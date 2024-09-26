///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Windows.H>
#include <STDIO.H>
#include <STDLib.H>

#include "../Shared/NTDBS.H"

#include "FileIO/ReadDelimited.H"
#include "FileIO/WriteDelimited.H"

int ReadDelimitedFile(char* fileName, char delimiter);
int FullyTestDB(int columns, int rowsPerColumn);
int ReadDBFile(char* fileName);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void main(void)
{
	FullyTestDB(100, 100);
	//ReadDBFile("C:\\DB.Txt");
	//ReadDelimitedFile("C:\\CSV.txt", ',');
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ReadDelimitedFile(char* fileName, char delimiter)
{
	_DatabaseSystem dbs;

	int totalColumns = 0;
	int totalRows = 0;

	printf("Calculating Delimited File...\n\n");
	CalculateDelimitedFile(&dbs, fileName, delimiter, &totalColumns, &totalRows);

	printf("Reading Delimited file...\n\n");
	ReadDelimitedFile(&dbs, fileName, delimiter, totalColumns, totalRows);

	int mostRows = GetMostRows(&dbs);

	printf("Reading %d rows from each of columns...\n\n", mostRows);
	int localLoop = 0;
	while (localLoop < dbs.Columns)
	{
		int internLoop = 0;

		while (internLoop < mostRows)
		{
			char result[128];

			RetrieveDataByColumnPosition(&dbs, localLoop, internLoop, result);

			int Length = RetrieveDataLengthByColumnPosition(&dbs, localLoop, internLoop);
			result[Length] = '\0';

			printf("Column-%d Row-%d: %s\n", localLoop, internLoop, result);

			internLoop++;
		}

		localLoop++;
	}

	printf("Freeing Database...\n\n");
	FreeDBS(&dbs);

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ReadDBFile(char* fileName)
{
	_DatabaseSystem dbs;

	int totalColumns = 0;
	int totalRows = 0;

	printf("Reading DB file...\n\n");
	ReadDBFile(&dbs, fileName);

	int mostRows = GetMostRows(&dbs);
	printf("Reading rows from each of columns...\n\n");
	int localLoop = 0;
	while (localLoop < dbs.Columns)
	{
		int internLoop = 0;

		while (internLoop < mostRows)
		{
			char result[128];

			RetrieveDataByColumnPosition(&dbs, localLoop, internLoop, result);

			int length = RetrieveDataLengthByColumnPosition(&dbs, localLoop, internLoop);
			result[length] = '\0';

			printf("Column-%d Row-%d: %s\n", localLoop, internLoop, result);

			internLoop++;
		}

		localLoop++;
	}

	printf("Freeing Database...\n\n");
	FreeDBS(&dbs);

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int FullyTestDB(int columns, int rowsPerColumn)
{
	int localLoop = 0;
	_DatabaseSystem dbs;

	InitializeDBS(&dbs, columns, rowsPerColumn);

	//--------------------------------------------------------
	printf("Adding %d columns...\n\n", columns);
	localLoop = 0;
	while (localLoop < columns)
	{
		char columnName[64];
		sprintf(columnName, "ColumnName_%d", localLoop);

		AddColumn(&dbs, columnName, strlen(columnName));

		localLoop++;
	}

	//--------------------------------------------------------
	printf("Adding %d rows to each of %d columns...\n\n", rowsPerColumn, columns);
	localLoop = 0;
	while (localLoop < columns)
	{
		char columnName[64];
		sprintf(columnName, "ColumnName_%d", localLoop);

		int internLoop = 0;
		while (internLoop < rowsPerColumn)
		{
			char rowData[64];
			sprintf(rowData, "%d->%d", localLoop, internLoop);

			AddEntryByColumnPosition(&dbs, localLoop, rowData, strlen(rowData));

			internLoop++;
		}

		localLoop++;
	}

	//  printf("Writing...\n\n");
	//  WriteDBFile(&dbs, "C:\\DB.Txt");
	//  WriteDelimitedFile(&dbs, "C:\\CSV.Txt", ',');

	//  DeleteRowByColumnName(&dbs, "ColumnName_9", 95);
	//  DeleteRowByColumnPosition(&dbs, 9, 95);

	//	char *NewData = "This row was deleted";
	//  AddEntryByColumnName(&dbs, "ColumnName_9", NewData, strlen(NewData));

		//--------------------------------------------------------
	printf("Reading %d rows from each of %d columns...\n\n", rowsPerColumn, columns);
	localLoop = 0;
	while (localLoop < columns)
	{
		int internLoop = 0;
		char columnName[64];
		sprintf(columnName, "ColumnName_%d", localLoop);

		while (internLoop < rowsPerColumn)
		{
			char result[1024];

			RetrieveDataByColumnName(&dbs, columnName, internLoop, result);

			int length = RetrieveDataLengthByColumnPosition(&dbs, localLoop, internLoop);
			result[length] = '\0';

			printf("Column-%d Row-%d: %s\n", localLoop, internLoop, result);

			internLoop++;
		}

		localLoop++;
	}

	//--------------------------------------------------------

	printf("Freeing Database...\n\n");
	FreeDBS(&dbs);

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

