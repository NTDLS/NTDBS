#ifndef _NTDBS_H
#define _NTDBS_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DllImport extern "C" __declspec( dllimport )
#define DllExport extern "C" __declspec( dllexport )

#define DBS_VOID                 0
#define DBS_CHAR                 1
#define DBS_UNSIGNED_CHAR        2
#define DBS_SHORT                3
#define DBS_UNSIGNED_SHORT       4
#define DBS_INT                  5
#define DBS_UNSIGNED_INT         6
#define DBS_LONG                 7
#define DBS_UNSIGNED_LONG        8
#define DBS_LONG_DOUBLE          9
#define DBS_UNSIGNED_LONG_DOUBLE 10
#define DBS_FLOAT                11
#define DBS_DOUBLE               12
#define DBS_BOOL                 13

#define DBS_GENERAL_OK                  1000
#define DBS_GENERAL_FATAL              -1001
#define DBS_GENERAL_NON_FATAL          -1002
#define DBS_FATAL_CORRUPTION           -1003
#define DBS_INITIALIZER_OUT_OF_BOUNDS  -1004
#define DBS_VALUE_OUT_OF_BOUNDS        -1005
#define DBS_GENERAL_INVALID_INPUT      -1006
#define DBS_VALUE_NOT_FOUND            -1007
#define DBS_FATAL_OUT_OF_MEMORY        -1008
#define DBS_NON_FATAL_OUT_OF_MEMORY    -1009
#define DBS_COLUMB_NOT_FOUND           -1010
#define DBS_ROW_NOT_FOUND              -1011
#define DBS_OVER_MAX_ROW_LIMIT         -1012
#define DBS_OVER_MAX_COLUMB_LIMIT      -1013

#define MAXDATASIZE      10240
#define MAXROWSPERCOLUMB 100000
#define MAXCOLUMBS       100000
#define MINROWSPERCOLUMB 1
#define MINCOLUMBS       1

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

const short _DBSTypeSize[] = {
	1,
	sizeof(char),
	sizeof(unsigned char),
	sizeof(short),
	sizeof(unsigned short),
	sizeof(int),
	sizeof(unsigned int),
	sizeof(long),
	sizeof(unsigned long),
	sizeof(long double),
	sizeof(long double),
	sizeof(float),
	sizeof(double),
	sizeof(bool)
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

