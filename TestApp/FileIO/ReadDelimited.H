#ifndef _DEFINED_NetWorkDLS_New_Technology_Data_Base_ReadDelimited
#define _DEFINED_NetWorkDLS_New_Technology_Data_Base_ReadDelimited
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Returns 0 is Delimiter is found, 1 if \n is found, 2 is EOF is found, otherwise 3
int ReadDelimitedDataFromFile(FILE* LocalSource, char* Buffer, int* Size, char Delimiter)
{
	char Char = 0;
	int Position = 0;
	int Marker = 0;

	Marker = fscanf(LocalSource, "%c", &Char);

	while (Char == ' ')
		Marker = fscanf(LocalSource, "%c", &Char);

	while (Marker != EOF)
	{
		BOOL Valid = TRUE;

		if (Char == '\r')
			Valid = FALSE;

		if (Char == '\n')
		{
			Buffer[Position] = '\0';
			*Size = Position;
			return 1;
		}

		if (Char == Delimiter)
		{
			Valid = FALSE;
			Buffer[Position] = '\0';
			*Size = Position;
			return 0;
		}

		if (Valid == TRUE)
		{
			Buffer[Position] = Char;
			Position++;
		}

		Marker = fscanf(LocalSource, "%c", &Char);
	}

	if (Marker == EOF) return 2;

	return 3;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL ReadDelimitedFile(struct _DatabaseSystem* dbs, char* FileName, char Delimiter, int xColumns, int xRowsPerColumn)
{
	char Buffer[1024];

	int DataSize = 0;
	int ReadResult = 0;
	int ColumnPosition = 0;

	FILE* LocalSource = NULL;

	if ((LocalSource = fopen(FileName, "rb")) == NULL)
	{
		return FALSE;
	}

	InitializeDBS(dbs, xColumns, xRowsPerColumn);

	// Add columns
	while (!ReadResult)
	{
		ReadResult = ReadDelimitedDataFromFile(LocalSource, Buffer, &DataSize, Delimiter);
		AddColumn(dbs, Buffer, DataSize);
	}

	if (ReadResult == 2 || ReadResult == 3) // Found EOF or did not find anything
		return FALSE;

	while (1)
	{
		ReadResult = 0;
		ColumnPosition = 0;

		while (!ReadResult)
		{
			ReadResult = ReadDelimitedDataFromFile(LocalSource, Buffer, &DataSize, Delimiter);

			if (ReadResult == 2 || ReadResult == 3) // Found EOF or found nothing
				break;

			AddEntryByColumnPosition(dbs, ColumnPosition, Buffer, DataSize);

			ColumnPosition++;
		}

		if (ReadResult == 2 || ReadResult == 3) // Found EOF or found nothing
			break;
	}

	if (LocalSource) fclose(LocalSource);

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CalculateDelimitedFile(struct _DatabaseSystem* dbs, char* FileName, char Delimiter, int* xTotalColumns, int* xTotalRows)
{
	char Buffer[1024];

	int DataSize = 0;
	int ReadResult = 0;
	int ColumnPosition = 0;
	int TotalColumns = 0;
	int TotalRows = 0;

	FILE* LocalSource = NULL;

	if ((LocalSource = fopen(FileName, "rb")) == NULL)
	{
		return FALSE;
	}

	// Count columns
	while (!ReadResult)
	{
		ReadResult = ReadDelimitedDataFromFile(LocalSource, Buffer, &DataSize, Delimiter);
		TotalColumns++;
	}

	if (ReadResult == 2 || ReadResult == 3) // Found EOF or did not find anything
		return FALSE;

	while (1)
	{
		ReadResult = 0;
		ColumnPosition = 0;

		while (!ReadResult)
		{
			ReadResult = ReadDelimitedDataFromFile(LocalSource, Buffer, &DataSize, Delimiter);

			if (ReadResult == 2 || ReadResult == 3) // Found EOF or found nothing
				break;

			ColumnPosition++;
		}

		TotalRows++;

		if (ReadResult == 2 || ReadResult == 3) // Found EOF or found nothing
			break;
	}

	if (LocalSource) fclose(LocalSource);

	*xTotalColumns = TotalColumns;
	*xTotalRows = TotalRows;

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

