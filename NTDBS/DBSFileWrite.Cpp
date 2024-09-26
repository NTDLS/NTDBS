#ifndef _DBSFileWrite_CPP
#define _DBSFileWrite_CPP
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Windows.H>
#include <Stdio.H>
#include <Stdlib.H>

#include "NTDBS.H"
#include "DBSFileWrite.H"
#include "DBSRoutines.H"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DllExport BOOL WriteDBFile(struct _DatabaseSystem* dbs, char* fileName)
{
	FILE* localTarget = NULL;

	if ((localTarget = fopen(fileName, "wb")) == NULL)
	{
		return FALSE;
	}

	int nameLength = 0;
	int columnRows = 0;
	int dataLength = 0;

	fwrite((char*)&dbs->MaxRowsPerColumn, sizeof(int), 1, localTarget);
	fwrite((char*)&dbs->MaxColumns, sizeof(int), 1, localTarget);
	fwrite((char*)&dbs->Columns, sizeof(int), 1, localTarget);

	int localLoop = 0;
	while (localLoop < dbs->Columns)
	{
		nameLength = dbs->Column[localLoop].NameLength;
		fwrite((char*)&nameLength, sizeof(int), 1, localTarget);
		fwrite((char*)dbs->Column[localLoop].Name, sizeof(char), nameLength, localTarget);
		localLoop++;
	}

	localLoop = 0;
	while (localLoop < dbs->Columns)
	{
		columnRows = dbs->Column[localLoop].Rows;
		fwrite((char*)&columnRows, sizeof(int), 1, localTarget);

		int InternLoop = 0;
		while (InternLoop < columnRows)
		{
			dataLength = dbs->Column[localLoop].Length[InternLoop];
			fwrite((char*)&dataLength, sizeof(int), 1, localTarget);
			fwrite((char*)dbs->Column[localLoop].Row[InternLoop], sizeof(char), dataLength, localTarget);
			InternLoop++;
		}

		localLoop++;
	}

	if (localTarget) fclose(localTarget);

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

