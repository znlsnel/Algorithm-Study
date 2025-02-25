using System;

public class Solution
{
        static int MOD = 1000000007;
        static int[] dx = { 1, 0, -1, 0 };
        static int[] dy = { 0, 1, 0, -1 };

        public int solution(int[, ] grid, int[] d, int k)
        {
                int n = grid.GetLength(0); // 행의 개수
                int m = grid.GetLength(1); // 열의 개수
                int dl = d.Length;

                // dp[순서][출발칸][목적지칸]
                long[][][] dp = new long[dl + 1][][];
                for (int i = 0; i <= dl; i++)
                {
                        dp[i] = new long[n * m][];
                        for (int j = 0; j < n * m; j++)
                        {
                                dp[i][j] = new long[n * m];
                        }
                }

                // 초기화: 시작점에서 시작점으로 이동하는 경우
                for (int i = 0; i < n * m; i++)
                {
                        dp[0][i][i] = 1;
                }

                // DP 배열 채우기
                for (int l = 1; l <= dl; l++)
                {
                        for (int i = 0; i < n * m; i++)
                        {
                                int x = i % m; // 열
                                int y = i / m; // 행

                                for (int dir = 0; dir < 4; dir++)
                                {
                                        int nx = x + dx[dir];
                                        int ny = y + dy[dir];

                                        // 범위를 벗어나거나 높이 차이가 d[l-1]와 일치하지 않으면 스킵
                                        if (nx < 0 || nx >= m || ny < 0 || ny >= n || grid[ny, nx] - grid[y, x] != d[l - 1])
                                        {
                                                continue;
                                        }

                                        // 이동 가능한 경우, 경로 수 업데이트
                                        for (int j = 0; j < n * m; j++)
                                        {
                                                dp[l][j][ny * m + nx] += dp[l - 1][j][i] % MOD;
                                                dp[l][j][ny * m + nx] %= MOD;
                                        }
                                }
                        }
                }

                // k를 2의 거듭제곱으로 분해하기 위해 필요한 최대 count 계산
                int count = 0;
                while (Math.Pow(2, count) < k)
                {
                        count++;
                }

                // edgePower[c]: dp[dl]를 2^c번 거듭제곱한 행렬
                long[][][] edgePower = new long[count + 1][][];
                for (int i = 0; i <= count; i++)
                {
                        edgePower[i] = new long[n * m][];
                        for (int j = 0; j < n * m; j++)
                        {
                                edgePower[i][j] = new long[n * m];
                        }
                }

                edgePower[0] = dp[dl]; // 초기값 설정
                for (int c = 1; c <= count; c++)
                {
                        edgePower[c] = MulMatrix(edgePower[c - 1], edgePower[c - 1]);
                }

                // 단위 행렬 초기화
                long[][] mat = new long[n * m][];
                for (int i = 0; i < n * m; i++)
                {
                        mat[i] = new long[n * m];
                        mat[i][i] = 1;
                }

                // k를 2의 거듭제곱으로 분해하여 행렬 곱셈 수행
                int kNum = k;
                while (kNum > 0)
                {
                        if (kNum >= Math.Pow(2, count))
                        {
                                mat = MulMatrix(mat, edgePower[count]);
                                kNum -= (int)Math.Pow(2, count);
                        }
                        count--;
                }

                // 모든 경로의 수 합산
                long answer = 0;
                for (int i = 0; i < n * m; i++)
                {
                        for (int j = 0; j < n * m; j++)
                        {
                                answer += mat[i][j];
                                answer %= MOD;
                        }
                }

                return (int)answer;
        }

        // 행렬 곱셈 메서드
        static long[][] MulMatrix(long[][] a, long[][] b)
        {
                int n = a.Length;
                long[][] result = new long[n][];
                for (int i = 0; i < n; i++)
                {
                        result[i] = new long[n];
                }

                for (int i = 0; i < n; i++)
                {
                        for (int j = 0; j < n; j++)
                        {
                                for (int l = 0; l < n; l++)
                                {
                                        result[i][j] += ((a[i][l] % MOD) * (b[l][j] % MOD)) % MOD;
                                        result[i][j] %= MOD;
                                }
                        }
                }

                return result;
        }
}