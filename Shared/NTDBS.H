#ifndef _DEFINED_NetWorkDLS_New_Technology_Database_System_Header
#define _DEFINED_NetWorkDLS_New_Technology_Database_System_Header
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DllImport         extern "C" __declspec( dllimport )

#define MAXDATASIZE      1048576
#define MAXROWSPERCOLUMB 1000000
#define MAXCOLUMBS       1000000
#define MINROWSPERCOLUMB 1
#define MINCOLUMBS       1

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct _DBSColumn {
	char** Row;     // Row Data              | Row[Row]      = "Row Data";
	int* Length;    // Length to row data    | Length[Row]   = 9;

	char* Name;     // Name of column        | Name          = "Column Name";
	int NameLength; // Length of column name | NameLength    = 11;
	int Rows;       // Rows in this column   | Rows          = 1255;
};

struct _DatabaseSystem {
	int MaxRowsPerColumn; //- Max rows per column    | MaxRowsPerColumn = 1000;
	int MaxColumns;       //- Max columns            | MaxColumns       = 100
	int Columns;          //- Current columns in DB  | Columns          = 57;
	_DBSColumn* Column;   //- Columns structure      | Column[Column Number]
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DllImport int InitializeDBS(struct _DatabaseSystem*, int, int);
DllImport int FreeDBS(struct _DatabaseSystem*);

DllImport int AddColumn(struct _DatabaseSystem*, char*, int);
DllImport int ColumnNameToColumnPosition(struct _DatabaseSystem*, char*);
DllImport int GetMostRows(struct _DatabaseSystem*);

DllImport int DeleteRowByColumnPosition(struct _DatabaseSystem*, int, int);
DllImport int DeleteRowByColumnName(struct _DatabaseSystem*, char*, int);

DllImport int AddEntryByColumnPosition(struct _DatabaseSystem*, int, char*, int);
DllImport int AddEntryByColumnName(struct _DatabaseSystem*, char*, char*, int);

DllImport int RetrieveDataLengthByColumnPosition(struct _DatabaseSystem*, int, int);
DllImport int RetrieveDataLengthByColumnName(struct _DatabaseSystem*, char*, int);

DllImport int SearchRowDataByColumnPosition(struct _DatabaseSystem*, int, char*);
DllImport int SearchRowDataByColumnName(struct _DatabaseSystem*, char*, char*);

DllImport int RetrieveDataByColumnPosition(struct _DatabaseSystem*, int, int, char*);
DllImport int RetrieveDataByColumnName(struct _DatabaseSystem*, char*, int, char*);

DllImport BOOL ReadDBFile(struct _DatabaseSystem*, char*);
DllImport BOOL WriteDBFile(struct _DatabaseSystem*, char*);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
