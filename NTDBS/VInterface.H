#ifndef _VInterface_H
#define _VInterface_H
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DllExport int VAddEntryByColumnPosition(struct _DatabaseSystem* dbs, int columnPos, void* rowData, int dataLength);
DllExport int VAddEntryByColumnName(struct _DatabaseSystem* dbs, char* columnName, void* rowData, int dataLength);
DllExport int VRetrieveDataByColumnPosition(struct _DatabaseSystem* dbs, int columnPos, int row, void* returnValue);
DllExport int VRetrieveDataByColumnName(struct _DatabaseSystem* dbs, char* columnName, int row, void* returnValue);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

