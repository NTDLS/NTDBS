#ifndef _DEFINED_NetWorkDLS_New_Technology_Data_Base_WriteDelimited
#define _DEFINED_NetWorkDLS_New_Technology_Data_Base_WriteDelimited
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL WriteDelimitedFile(struct _DatabaseSystem* dbs, char* FileName, char Delimiter)
{
	FILE* LocalTarget = NULL;

	if ((LocalTarget = fopen(FileName, "wb")) == NULL)
	{
		return FALSE;
	}

	int LocalLoop = 0;
	while (LocalLoop < dbs->Columns)
	{
		int NameLength = dbs->Column[LocalLoop].NameLength;
		fwrite(dbs->Column[LocalLoop].Name, sizeof(char), NameLength, LocalTarget);

		if ((LocalLoop + 1) < dbs->Columns)
			fprintf(LocalTarget, "%c", Delimiter);

		LocalLoop++;
	}

	fprintf(LocalTarget, "\r\n");

	int ColumnPosition = 0;
	int RowPosition = 0;

	int MostRows = GetMostRows(dbs);

	LocalLoop = 0;
	while (LocalLoop < MostRows)
	{
		int InternLoop = 0;
		while (InternLoop < dbs->Columns)
		{
			int DataLength = dbs->Column[InternLoop].Length[RowPosition];

			if (DataLength > 0)
				fwrite(dbs->Column[InternLoop].Row[RowPosition], sizeof(char), DataLength, LocalTarget);
			else fprintf(LocalTarget, "\"\"");

			if ((InternLoop + 1) < dbs->Columns)
				fprintf(LocalTarget, "%c", Delimiter);

			InternLoop++;
		}

		fprintf(LocalTarget, "\r\n");

		RowPosition++;
		LocalLoop++;
	}

	if (LocalTarget) fclose(LocalTarget);

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

