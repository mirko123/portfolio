using System;
using System.IO;
//using Excel = Microsoft.Office.Interop.Excel;
using ExcelLibrary.CompoundDocumentFormat;
using ExcelLibrary.SpreadSheet;
using System.Collections.Generic;

namespace Optimizer
{

    class CreateExcelDoc
    {
        string file;
        public CreateExcelDoc(string FileName)
        {
            file = FileName;
            string Directory = "";
            string path = Path.Combine(Directory, FileName);
            if (!File.Exists(path))
            {
                Workbook workbook = new Workbook();
                Worksheet worksheet = new Worksheet("First Sheet");
                worksheet.Cells[0, 0] = new Cell("Days");
                worksheet.Cells.ColumnWidth[0, 1] = 3000;
                workbook.Worksheets.Add(worksheet);
                workbook.Save(file);
            }
        }
        public string Read(int row, int col)
        {
            Workbook book = Workbook.Load(file);
            Worksheet sheet = book.Worksheets[0];
            if (sheet.Cells[row, col].Value == null)
                return null;
            else
                return sheet.Cells[row, col].Value.ToString();
        }

        public string[] ReadArrayFromCol(int col, int from, int length)
        {
            Workbook book = Workbook.Load(file);
            Worksheet sheet = book.Worksheets[0];
            string[] str = new string[length];
            for (int row = from; row < from + length; row++)
            {
                if (sheet.Cells[row, col].Value != null) str[row - from] = sheet.Cells[row, col].StringValue;
                else str[row - from] = null;
            }
            return str;
        }
        public string[] ReadArrayFromRow(int row, int from, int length)
        {
            Workbook book = Workbook.Load(file);
            Worksheet sheet = book.Worksheets[0];
            string[] str = new string[length];
            for (int col = from; col < from + length; col++)
            {
                if (sheet.Cells[row, col].Value != null) str[col - from] = sheet.Cells[row, col].StringValue;
                else str[col - from] = null;
            }
            return str;
        }
        public string[,] ReadMatrix()
        {
            List<string> list1 = new List<string>();
            //  
            //  str1[2,2]="2";
            Workbook book = Workbook.Load(file);
            Worksheet sheet = book.Worksheets[0];
            int rows = 0;
            while (sheet.Cells[rows, 0].Value != null)
            {
                rows++;
            }
            string[,] str = new string[rows, 8];
            for (int row = 0; row < rows; row++)
            {
                for (int col = 0; col < 8; col++)
                {
                    if (sheet.Cells[row, col].Value != null)
                        str[row, col] = sheet.Cells[row, col].StringValue;
                    else str[row, col] = "0";
                }
            }
            return str;
        }
        public void AddMatrix(string[,] matrix)
        {
            Workbook book = Workbook.Load(file);
            Worksheet sheet = book.Worksheets[0];
            for (int row = 0; row < matrix.GetLength(0); row++)
            {
                for (int col = 0; col < matrix.GetLength(1); col++)
                {
                    sheet.Cells[row, col] = new Cell(matrix[row, col]);
                }
            }
            book.Worksheets[0] = sheet;
            book.Save(file);
        }
        public void AddData(int row, int col, string str)
        {
            Workbook book = Workbook.Load(file);
            Worksheet sheet = book.Worksheets[0];
            sheet.Cells[row, col] = new Cell(str);
            book.Worksheets[0] = sheet;
            book.Save(file);
        }
        public void AddArrayInRow(int row, int from, string[] strArr)
        {
            Workbook book = Workbook.Load(file);
            Worksheet sheet = book.Worksheets[0];
            for (int col = from; col < from + strArr.Length; col++)
            {
                sheet.Cells[row, col] = new Cell(strArr[col - from]);
            }
            book.Worksheets.Add(sheet);
            book.Save(file);
        }
        public void AddArrayInCol(int col, int from, string[] strArr)
        {
            Workbook book = Workbook.Load(file);
            Worksheet sheet = book.Worksheets[0];
            for (int row = from; row < from + strArr.Length; row++)
            {
                sheet.Cells[row, col] = new Cell(strArr[row - from]);
            }
            book.Worksheets[0] = sheet;
            book.Save(file);
        }
        public int CountColls(int rows)
        {
            int i = 0;
            Workbook book = Workbook.Load(file);
            Worksheet sheet = book.Worksheets[0];
            while (sheet.Cells[rows, i].Value != null)
                i++;
            return i;
        }
        public int CountRows(int cols)
        {
            int i = 0;
            Workbook book = Workbook.Load(file);
            Worksheet sheet = book.Worksheets[0];
            while (sheet.Cells[i, cols].Value != null)
                i++;
            return i;
        }
        public string[][] NewDate(string date, int Length)
        {
            Workbook book = Workbook.Load(file);
            Worksheet sheet = book.Worksheets[0];
            string[][] day = new String[8][];
            day[0] = new String[Length];
            day[1] = new String[Length];
            day[2] = new String[Length];
            day[3] = new String[Length];
            day[4] = new String[Length];
            day[5] = new String[Length];
            day[6] = new String[Length];
            day[7] = new String[Length];
            if (sheet.Cells[0, 7].Value == null)
            {
                for (int col = 1; col < 8; col++)
                {
                    for (int row = 0; row < Length; row++)
                    {
                        sheet.Cells[row, col] = new Cell("0");
                    }
                }
            }
            if (sheet.Cells[0, 7].StringValue != date)
            {
                for (int col = 1; col < 7; col++)
                {
                    for (int row = 0; row < Length; row++)
                    {
                        sheet.Cells[row, col] = new Cell(sheet.Cells[row, col + 1].StringValue);
                        if (row == 0 && col == 6) sheet.Cells[row, 7] = new Cell(date);
                        if (row > 0 && col == 6) sheet.Cells[row, 7] = new Cell("0");
                    }
                }
            }
            for (int col = 0; col < 8; col++)
            {
                for (int row = 0; row < Length; row++)
                {
                    day[col][row] = sheet.Cells[row, col].StringValue;
                }
            }
            book.Worksheets[0] = sheet;
            book.Save(file);
            return day;
        }
    }
}

