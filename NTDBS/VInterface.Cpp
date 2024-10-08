#ifndef _VInterface_CPP
#define _VInterface_CPP
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Windows.H>
#include <Stdio.H>
#include <Stdlib.H>

#include "NTDBS.H"
#include "VInterface.H"
#include "DBSRoutines.H"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DllExport int VAddEntryByColumnPosition(struct _DatabaseSystem* dbs, int columnPos, void* rowData, int dataLength)
{
	return AddEntryByColumnPosition(dbs, columnPos, (char*)rowData, dataLength);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DllExport int VAddEntryByColumnName(struct _DatabaseSystem* dbs, char* columnName, void* rowData, int dataLength)
{
	return AddEntryByColumnName(dbs, columnName, (char*)rowData, dataLength);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DllExport int VRetrieveDataByColumnPosition(struct _DatabaseSystem* dbs, int columnPos, int row, void* returnValue)
{
	return RetrieveDataByColumnPosition(dbs, columnPos, row, (char*)returnValue);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DllExport int VRetrieveDataByColumnName(struct _DatabaseSystem* dbs, char* columnName, int row, void* returnValue)
{
	return RetrieveDataByColumnName(dbs, columnName, row, (char*)returnValue);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

