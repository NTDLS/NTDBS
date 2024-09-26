#ifndef _DBSRoutines_CPP
#define _DBSRoutines_CPP
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Windows.H>
#include <Stdio.H>
#include <Stdlib.H>

#include "NTDBS.H"
#include "DBSRoutines.H"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DllExport short SizeOfType(int Type)
{
	return _DBSTypeSize[Type];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DllExport int InitializeDBS(struct _DatabaseSystem* dbs, int columns, int rowsPerColumn)
{
	if ((columns > MAXCOLUMBS) || (columns < MINCOLUMBS))
		return DBS_INITIALIZER_OUT_OF_BOUNDS;

	if ((rowsPerColumn > MAXROWSPERCOLUMB) || (rowsPerColumn < MINROWSPERCOLUMB))
		return DBS_INITIALIZER_OUT_OF_BOUNDS;

	dbs->MaxRowsPerColumn = rowsPerColumn;
	dbs->MaxColumns = columns;

	dbs->Column = (_DBSColumn*)calloc(sizeof(_DBSColumn), columns);
	if (dbs->Column == NULL)
		return DBS_FATAL_OUT_OF_MEMORY;

	dbs->Columns = 0;

	return DBS_GENERAL_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DllExport int FreeDBS(struct _DatabaseSystem* dbs)
{
	int localLoop = 0;

	while (localLoop < dbs->Columns)
	{
		int internLoop = 0;
		while (internLoop < dbs->Column[localLoop].Rows)
		{
			free(dbs->Column[localLoop].Row[internLoop]);

			dbs->Column[localLoop].Row[internLoop] = NULL;
			dbs->Column[localLoop].Length[internLoop] = 0;

			internLoop++;
		}

		free(dbs->Column[localLoop].Length);
		free(dbs->Column[localLoop].Row);
		free(dbs->Column[localLoop].Name);

		dbs->Column[localLoop].Rows = 0;
		dbs->Column[localLoop].NameLength = 0;

		localLoop++;
	}

	dbs->MaxRowsPerColumn = 0;
	dbs->MaxColumns = 0;
	dbs->Columns = 0;

	free(dbs->Column);

	return DBS_GENERAL_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DllExport int AddColumn(struct _DatabaseSystem* dbs, char* columnName, int nameLength)
{
	if (dbs->Columns >= dbs->MaxColumns)
		return DBS_OVER_MAX_COLUMB_LIMIT;

	dbs->Column[dbs->Columns].Name = (char*)calloc(nameLength + 1, 1);
	if (dbs->Column[dbs->Columns].Name == NULL)
		return DBS_NON_FATAL_OUT_OF_MEMORY;

	dbs->Column[dbs->Columns].Row = (char**)calloc(sizeof(char*), dbs->MaxRowsPerColumn);
	if (dbs->Column[dbs->Columns].Row == NULL)
		return DBS_NON_FATAL_OUT_OF_MEMORY;

	dbs->Column[dbs->Columns].Length = (int*)calloc(sizeof(int*), dbs->MaxRowsPerColumn);
	if (dbs->Column[dbs->Columns].Length == NULL)
		return DBS_NON_FATAL_OUT_OF_MEMORY;

	dbs->Column[dbs->Columns].Rows = 0;

	dbs->Column[dbs->Columns].NameLength = nameLength;

	memcpy(dbs->Column[dbs->Columns].Name, columnName, nameLength);

	dbs->Columns++;

	return DBS_GENERAL_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DllExport int ColumnNameToColumnPosition(struct _DatabaseSystem* dbs, char* columnName)
{
	int localLoop = 0;

	while (localLoop < dbs->Columns)
	{
		if (strcmp(dbs->Column[localLoop].Name, columnName) == 0)
			return localLoop;

		localLoop++;
	}

	return DBS_COLUMB_NOT_FOUND;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DllExport int GetMostRows(struct _DatabaseSystem* dbs)
{
	int localLoop = 0;

	int mostRows = -1;

	while (localLoop < dbs->Columns)
	{
		int Rows = dbs->Column[localLoop].Rows;

		if (Rows > mostRows)
			mostRows = Rows;

		localLoop++;
	}

	return mostRows;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DllExport int DeleteRowByColumnPosition(struct _DatabaseSystem* dbs, int columnPos, int row)
{
	if (columnPos >= dbs->MaxColumns)
		return DBS_OVER_MAX_COLUMB_LIMIT;

	if (columnPos >= dbs->Columns)
		return DBS_COLUMB_NOT_FOUND;

	if (row >= dbs->MaxRowsPerColumn)
		return DBS_OVER_MAX_ROW_LIMIT;

	if (row >= dbs->Column[columnPos].Rows)
		return DBS_ROW_NOT_FOUND;

	free(dbs->Column[columnPos].Row[row]);

	dbs->Column[columnPos].Length[row] = 0;

	int localLoop = row;

	while (localLoop < dbs->Column[columnPos].Rows)
	{
		dbs->Column[columnPos].Row[localLoop] = dbs->Column[columnPos].Row[localLoop + 1];
		dbs->Column[columnPos].Length[localLoop] = dbs->Column[columnPos].Length[localLoop + 1];
		localLoop++;
	}

	dbs->Column[columnPos].Rows--;

	return DBS_GENERAL_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DllExport int DeleteRowByColumnName(struct _DatabaseSystem* dbs, char* columnName, int row)
{
	int columnPos = 0;

	if ((columnPos = ColumnNameToColumnPosition(dbs, columnName)) < 0)
		return columnPos;

	return DeleteRowByColumnPosition(dbs, columnPos, row);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DllExport int AddEntryByColumnPosition(struct _DatabaseSystem* dbs, int columnPos, char* rowData, int dataLength)
{
	int rows = dbs->Column[columnPos].Rows;

	if ((dataLength > MAXDATASIZE) || (dataLength < 0))
		return DBS_VALUE_OUT_OF_BOUNDS;

	if (rows >= dbs->MaxRowsPerColumn)
		return DBS_OVER_MAX_ROW_LIMIT;

	if (columnPos >= dbs->MaxColumns)
		return DBS_OVER_MAX_COLUMB_LIMIT;

	dbs->Column[columnPos].Row[rows] = (char*)calloc(dataLength + 1, 1);
	if (dbs->Column[columnPos].Row[rows] == NULL)
		return DBS_NON_FATAL_OUT_OF_MEMORY;

	dbs->Column[columnPos].Length[rows] = dataLength;

	memcpy(dbs->Column[columnPos].Row[rows], rowData, dataLength);

	dbs->Column[columnPos].Rows++;

	return DBS_GENERAL_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DllExport int AddEntryByColumnName(struct _DatabaseSystem* dbs, char* columnName, char* rowData, int dataLength)
{
	int columnPos = 0;

	if ((columnPos = ColumnNameToColumnPosition(dbs, columnName)) < 0)
		return DBS_COLUMB_NOT_FOUND;

	return AddEntryByColumnPosition(dbs, columnPos, rowData, dataLength);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DllExport int SearchRowDataByColumnPosition(struct _DatabaseSystem* dbs, int column, char* search)
{
	int localLoop = 0;

	if (column > dbs->Columns)
		return DBS_COLUMB_NOT_FOUND;

	while (localLoop < dbs->Column[column].Rows)
	{
		if (strcmp(dbs->Column[column].Row[localLoop], search) == 0)
			return localLoop;

		localLoop++;
	}

	return DBS_ROW_NOT_FOUND;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DllExport int SearchRowDataByColumnName(struct _DatabaseSystem* dbs, char* columnName, char* search)
{
	int columnPos = 0;

	if ((columnPos = ColumnNameToColumnPosition(dbs, columnName)) < 0)
		return DBS_COLUMB_NOT_FOUND;

	return SearchRowDataByColumnPosition(dbs, columnPos, search);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DllExport int RetrieveDataLengthByColumnPosition(struct _DatabaseSystem* dbs, int columnPos, int row)
{
	if (columnPos > dbs->Columns)
		return DBS_COLUMB_NOT_FOUND;

	if (row >= dbs->Column[columnPos].Rows)
		return DBS_ROW_NOT_FOUND;

	return dbs->Column[columnPos].Length[row];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DllExport int RetrieveDataLengthByColumnName(struct _DatabaseSystem* dbs, char* columnName, int row)
{
	int columnPos = 0;

	if ((columnPos = ColumnNameToColumnPosition(dbs, columnName)) < 0)
		return DBS_COLUMB_NOT_FOUND;

	return RetrieveDataLengthByColumnPosition(dbs, columnPos, row);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DllExport int RetrieveDataByColumnPosition(struct _DatabaseSystem* dbs, int columnPos, int row, char* returnValue)
{
	if (columnPos > dbs->Columns)
		return DBS_COLUMB_NOT_FOUND;

	if (row >= dbs->Column[columnPos].Rows)
		return DBS_ROW_NOT_FOUND;

	int Length = dbs->Column[columnPos].Length[row];

	memcpy(returnValue, dbs->Column[columnPos].Row[row], Length);

	return DBS_GENERAL_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DllExport int RetrieveDataByColumnName(struct _DatabaseSystem* dbs, char* columnName, int row, char* returnValue)
{
	int columnPos = 0;

	if ((columnPos = ColumnNameToColumnPosition(dbs, columnName)) < 0)
		return DBS_COLUMB_NOT_FOUND;

	return RetrieveDataByColumnPosition(dbs, columnPos, row, returnValue);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

