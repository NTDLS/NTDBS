#ifndef _DBSFileRead_CPP
#define _DBSFileRead_CPP
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Windows.H>
#include <Stdio.H>
#include <Stdlib.H>

#include "NTDBS.H"
#include "DBSFileRead.H"
#include "DBSRoutines.H"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DllExport BOOL ReadDBFile(struct _DatabaseSystem* dbs, char* fileName)
{
	FILE* localSource = NULL;

	if ((localSource = fopen(fileName, "rb")) == NULL)
	{
		return FALSE;
	}

	char* buffer = NULL;

	int nameLength = 0;
	int bytesRead = 0;
	int dataLength = 0;

	int maxRowsPerColumn = 0;
	int maxColumns = 0;
	int columns = 0;

	fread((char*)&maxRowsPerColumn, sizeof(int), 1, localSource);
	fread((char*)&maxColumns, sizeof(int), 1, localSource);
	fread((char*)&columns, sizeof(int), 1, localSource);

	InitializeDBS(dbs, maxColumns, maxRowsPerColumn);

	buffer = (char*)calloc(MAXDATASIZE + 1, 1);

	if (buffer == NULL)
		return FALSE;

	int localLoop = 0;
	while (localLoop < columns)
	{
		fread((char*)&nameLength, sizeof(int), 1, localSource);
		bytesRead = fread(buffer, sizeof(char), nameLength, localSource);

		AddColumn(dbs, buffer, bytesRead);
		localLoop++;
	}

	localLoop = 0;
	while (localLoop < columns)
	{
		int ColumnRows = 0;
		fread((char*)&ColumnRows, sizeof(int), 1, localSource);

		int InternLoop = 0;
		while (InternLoop < ColumnRows)
		{
			fread((char*)&dataLength, sizeof(int), 1, localSource);
			bytesRead = fread(buffer, sizeof(char), dataLength, localSource);
			AddEntryByColumnPosition(dbs, localLoop, buffer, bytesRead);
			InternLoop++;
		}

		localLoop++;
	}

	free(buffer);

	if (localSource) fclose(localSource);

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

