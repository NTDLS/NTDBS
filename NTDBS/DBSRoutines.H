#ifndef _DBSRoutines_H
#define _DBSRoutines_H
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DllExport int AddColumn(struct _DatabaseSystem* dbs, char* columnName, int nameLength);
DllExport int AddEntryByColumnName(struct _DatabaseSystem* dbs, char* columnName, char* rowData, int dataLength);
DllExport int AddEntryByColumnPosition(struct _DatabaseSystem* dbs, int columnPos, char* rowData, int dataLength);
DllExport int ColumnNameToColumnPosition(struct _DatabaseSystem* dbs, char* columnName);
DllExport int DeleteRowByColumnName(struct _DatabaseSystem* dbs, char* columnName, int row);
DllExport int DeleteRowByColumnPosition(struct _DatabaseSystem* dbs, int columnPos, int row);
DllExport int FreeDBS(struct _DatabaseSystem* dbs);
DllExport int GetMostRows(struct _DatabaseSystem* dbs);
DllExport int InitializeDBS(struct _DatabaseSystem* dbs, int columns, int rowsPerColumn);
DllExport int RetrieveDataByColumnName(struct _DatabaseSystem* dbs, char* columnName, int row, char* returnValue);
DllExport int RetrieveDataByColumnPosition(struct _DatabaseSystem* dbs, int columnPos, int row, char* returnValue);
DllExport int RetrieveDataLengthByColumnName(struct _DatabaseSystem* dbs, char* columnName, int row);
DllExport int RetrieveDataLengthByColumnPosition(struct _DatabaseSystem* dbs, int columnPos, int row);
DllExport int SearchRowDataByColumnName(struct _DatabaseSystem* dbs, char* columnName, char* search);
DllExport int SearchRowDataByColumnPosition(struct _DatabaseSystem* dbs, int column, char* search);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

