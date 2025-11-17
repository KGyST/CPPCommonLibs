#include	"Logger.hpp"
#include	"../WinReg/WinReg.hpp"
#include	"loglevelStrings.hpp"

#define		EOLInFile		"\xD\xA"
#define		EOLInFile_LEN	2


// =====================================================================================================================
//
// File I/O
//
// =====================================================================================================================

// -----------------------------------------------------------------------------
//	Open the file
// -----------------------------------------------------------------------------

GSErrCode Logger::OpenLogFileForWriting()
{
	GSErrCode	errCode = NoError;

	if (m_pLogFile != nullptr)
		return Error;

	errCode = IO::fileSystem.CreateFolderTree(*m_pLogFileFolder);

	if (errCode == IO::fileSystem.TargetExists)
		errCode = NoError;

	try {
		auto pFullPath = *m_pLogFileFolder;
		pFullPath.AppendToLocal(IO::Name(m_logFileName));

		m_pLogFile = new IO::File(pFullPath, IO::File::Create);
		if (m_pLogFile == nullptr)
			throw GS::GeneralException();
	}
	catch (...) {
		if (m_pLogFile != nullptr) {
			delete m_pLogFile;
			m_pLogFile = nullptr;
		}

		throw GS::GeneralException();
	}

	errCode = m_pLogFile->GetStatus();
	if (errCode == NoError)
		errCode = m_pLogFile->Open(IO::File::AppendMode);

	if (errCode != NoError) {
		m_pLogFile->Close();

		delete m_pLogFile;
		m_pLogFile = nullptr;

		throw GS::GeneralException();
	}

	if (m_pLogFile != nullptr)
		m_pLogFile->WriteBin("\xEF\xBB\xBF", 3);	// make it UTF-8

	return NoError;
}

// -----------------------------------------------------------------------------
//	Close the file
// -----------------------------------------------------------------------------

GSErrCode Logger::CloseLogFile(void)
{
	GSErrCode lastErr = NoError;

	if (m_pLogFile != nullptr)
	{
		lastErr = m_pLogFile->Close();
		m_pLogFile = nullptr;
	}

	return lastErr;
}		// Close

// -----------------------------------------------------------------------------
//	Write a unicode string into the open file
// -----------------------------------------------------------------------------

GSErrCode Logger::Write(const GS::UniString& val)
{
	GSErrCode lastErr = NoError;

	if (lastErr != NoError)
		return lastErr;

	Int32 length = Strlen32(val.ToCStr(0, MaxUSize, CC_UTF8).Get());
	char* cBuffer = nullptr;
	try {
		cBuffer = new char[length + 1];	// buffer_overrun_reviewed_0
		if (cBuffer != nullptr) {
			CHCopyC(val.ToCStr(0, MaxUSize, CC_UTF8).Get(), cBuffer);
			lastErr = m_pLogFile->WriteBin(cBuffer, length);
		}
		else {
			lastErr = ErrMemoryFull;
		}
	}
	catch (...) {
		lastErr = Error;
	}
	if (cBuffer != nullptr)
		delete[] cBuffer;

	return lastErr;
}		// Write

// -----------------------------------------------------------------------------
//	Write into the open file
// -----------------------------------------------------------------------------

GSErrCode Logger::Write(Int32 nBytes, GSPtr data)
{
	GSErrCode lastErr = NoError;

	if (lastErr != NoError)
		return lastErr;

	lastErr = m_pLogFile->WriteBin(data, nBytes);

	return lastErr;
}		// Write

// -----------------------------------------------------------------------------
//	Write a unicode string into the open file
// -----------------------------------------------------------------------------

GSErrCode Logger::AddToLogFile(const GS::UniString& i_logRow)
{
	GSErrCode lastErr = NoError;

	if (lastErr != NoError)
		return lastErr;

	Int32 length = Strlen32(i_logRow.ToCStr(0, MaxUSize, CC_UTF8).Get());
	char* cBuffer = nullptr;
	try {
		cBuffer = new char[length + 1];	// buffer_overrun_reviewed_0
		if (cBuffer != nullptr) {
			CHCopyC(i_logRow.ToCStr(0, MaxUSize, CC_UTF8).Get(), cBuffer);
			lastErr = m_pLogFile->WriteBin(cBuffer, length);
		}
		else {
			lastErr = ErrMemoryFull;
		}
	}
	catch (...) {
		lastErr = Error;
	}
	if (cBuffer != nullptr)
		delete[] cBuffer;

	return lastErr;
}		// Write

// -----------------------------------------------------------------------------
//	Write a newline into the file
// -----------------------------------------------------------------------------

GSErrCode Logger::WrNewLine(void)
{
	GSErrCode lastErr = NoError;

	m_pLogFile->WriteBin(EOLInFile, EOLInFile_LEN);

	return lastErr;
}		// WrNewLine

GSErrCode	Logger::WriteStr(const char* val, NewLineFlag newLine /* = NoNewLine*/)
{
	GSErrCode lastErr = NoError;

	char	buffer[512];

	sprintf(buffer, "%s ", val);
	Write(Strlen32(buffer), buffer);

	if (newLine == WithNewLine)
		WrNewLine();

	return lastErr;
}		// WriteStr

// -----------------------------------------------------------------------------
//	Write a unicode string value into the file
// -----------------------------------------------------------------------------

GSErrCode	Logger::WriteStr(const GS::UniString& val, NewLineFlag newLine /* = NoNewLine*/)
{
	GSErrCode lastErr = NoError;

	Write(val + " ");

	if (newLine == WithNewLine)
		WrNewLine();

	return lastErr;
}		// WriteStr

const GS::UniString Logevent::ToUniString() const
{
	return m_sDate + ": " + m_sLogText;
}

// =====================================================================================================================

Logger::Logger(const GS::UniString& i_compName, const GS::UniString& i_appName)
	: m_regPath("SOFTWARE\\" + i_compName + "\\" + i_appName)
	, m_loglevel(LogLev_DEBUG)
{
	GS::UniString fileName = i_appName + GetTimeStr("%Y%m%d_%H%M%S") + GS::UniString(".log");

	GS::UniString sLogFolder = GetRegString(m_regPath, GS::UniString("LogFileFolder"));

	if (sLogFolder.GetLength() > 0)
	{
		SetLogFileFolder(IO::Location(sLogFolder), fileName);
	}
	else
	{
		IO::Location loc;

		GSErrCode err = IO::fileSystem.GetSpecialLocation(IO::FileSystem::TemporaryFolder, &loc);

		loc.AppendToLocal(IO::Name(i_compName));
		loc.AppendToLocal(IO::Name(i_appName));

		SetLogFileFolder(loc, fileName);
	}
}

Logger::~Logger()
{
	delete m_pLogFileFolder;

	GS::UniString _path;
	m_pLogFileFolder->ToPath(&_path);

	SetRegString(_path, "LogFileFolder", m_regPath);
}

// =====================================================================================================================
//
// Actual logger functions
//
// =====================================================================================================================

void Logger::Log(const GS::UniString& i_sLogText,
	const GSErrCode i_errCode,
	const Loglevel i_logLevel /*= LogLev_DEBUG*/,
	const GS::Guid* const i_guid /*= nullptr*/)
{
	if (i_logLevel >= GetLoglevel())
	{
		OpenLogFileForWriting();

		char sError[16];

		itoa((short)i_logLevel, sError, 10);

		GS::UniString _s = i_guid ? (GS::UniString(" GUID: ") + ((*i_guid).ToUniString())) : GS::UniString("");

		const GS::UniString sLogEntry = GetTimeStr("%H:%M:%S") +
			" " + sLoglevels[(int)i_logLevel] +
			": " + i_sLogText +
			_s +
			" Error Code: " + sError;

		Write(sLogEntry);

		WrNewLine();

		CloseLogFile();
	}
}

void Logger::Log(const Logevent& i_logevent)
{
	if (i_logevent.GetLogLevel() > m_loglevel)
	{
		OpenLogFileForWriting();

		Write(i_logevent.ToUniString());

		WrNewLine();

		CloseLogFile();
	}
}

// Getters / Setters

GS::UniString Logger::GetLogFileFolderStr() const
{
	GS::UniString n;
	m_pLogFileFolder->ToPath(&n);

	return (n);
}

void Logger::SetLogFileFolder(IO::Location& i_loc, GS::UniString& i_fileName)
{ 
	m_pLogFileFolder = new IO::Location(i_loc);
	m_logFileName = i_fileName;

	OpenLogFileForWriting();

	Write("Logging started: " + GetTimeStr("%Y.%m.%d %H:%M:%S"));

	WrNewLine();

	CloseLogFile();
}

