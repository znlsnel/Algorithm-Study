using System;
using System.Collections.Generic;

public class Solution
{
        private const int MODULER = 10000019;

        public void CalculateCombination(long[, ] V, int Row)
        {
                V[0, 0] = 1;
                for (int i = 1; i <= Row; i++)
                {
                        for (int j = 0; j <= Row; j++)
                        {
                                if (j == 0) V[i, j] = 1;
                                else if (i == j) V[i, j] = 1;
                                else V[i, j] = (V[i - 1, j - 1] + V[i - 1, j]) % MODULER;
                        }
                }
        }

        public void CalculateOneCnt(int[] V, int[, ] MAP)
        {
                int row = MAP.GetLength(0);
                int col = MAP.GetLength(1);
                for (int i = 0; i < row; i++)
                {
                        for (int j = 0; j < col; j++)
                        {
                                V[j] += MAP[i, j];
                        }
                }
        }

        public int solution(int[, ] a)
        {
                int Row = a.GetLength(0);
                int Col = a.GetLength(1);

                long[, ] nCr = new long[Row + 1, Row + 1];
                CalculateCombination(nCr, Row);

                int[] ArrOneCnt = new int[Col + 1];
                CalculateOneCnt(ArrOneCnt, a);

                long[, ] DP = new long[Col + 2, Row + 1];
                DP[1, Row - ArrOneCnt[0]] = nCr[Row, Row - ArrOneCnt[0]];

                for (int Column = 1; Column < Col; Column++)
                {
                        int OneCnt = ArrOneCnt[Column];
                        for (int EvenNum = 0; EvenNum <= Row; EvenNum++)
                        {
                                if (DP[Column, EvenNum] == 0) continue;
                                for (int K = 0; K <= OneCnt; K++)
                                {
                                        if (EvenNum < K) continue;
                                        int BeEvenRow = EvenNum + OneCnt - (2 * K);
                                        if (BeEvenRow > Row) continue;

                                        long Result = (nCr[EvenNum, K] * nCr[Row - EvenNum, OneCnt - K]) % MODULER;
                                        DP[Column + 1, BeEvenRow] = (DP[Column + 1, BeEvenRow] + DP[Column, EvenNum] * Result) % MODULER;
                                }
                        }
                }

                return (int)DP[Col, Row];
        }
}