#define NB 4  // number of coloumn of State (for AES = 4)
#define NR 10 // number of rounds ib ciper cycle (if nb = 4 nr = 10)
#define NK 4  // the key length (in 32-bit words)

int sbox[] = {
    99, 124, 119, 123, 242, 107, 111, 197, 48, 1, 103, 43, 254, 215, 171, 118,
    202, 130, 201, 125, 250, 89, 71, 240, 173, 212, 162, 175, 156, 164, 114, 192,
    183, 253, 147, 38, 54, 63, 247, 204, 52, 165, 229, 241, 113, 216, 49, 21,
    4, 199, 35, 195, 24, 150, 5, 154, 7, 18, 128, 226, 235, 39, 178, 117,
    9, 131, 44, 26, 27, 110, 90, 160, 82, 59, 214, 179, 41, 227, 47, 132,
    83, 209, 0, 237, 32, 252, 177, 91, 106, 203, 190, 57, 74, 76, 88, 207,
    208, 239, 170, 251, 67, 77, 51, 133, 69, 249, 2, 127, 80, 60, 159, 168,
    81, 163, 64, 143, 146, 157, 56, 245, 188, 182, 218, 33, 16, 255, 243, 210,
    205, 12, 19, 236, 95, 151, 68, 23, 196, 167, 126, 61, 100, 93, 25, 115,
    96, 129, 79, 220, 34, 42, 144, 136, 70, 238, 184, 20, 222, 94, 11, 219,
    224, 50, 58, 10, 73, 6, 36, 92, 194, 211, 172, 98, 145, 149, 228, 121,
    231, 200, 55, 109, 141, 213, 78, 169, 108, 86, 244, 234, 101, 122, 174, 8,
    186, 120, 37, 46, 28, 166, 180, 198, 232, 221, 116, 31, 75, 189, 139, 138,
    112, 62, 181, 102, 72, 3, 246, 14, 97, 53, 87, 185, 134, 193, 29, 158,
    225, 248, 152, 17, 105, 217, 142, 148, 155, 30, 135, 233, 206, 85, 40, 223,
    140, 161, 137, 13, 191, 230, 66, 104, 65, 153, 45, 15, 176, 84, 187, 22};

int inv_sbox[] = {
    82, 9, 106, 213, 48, 54, 165, 56, 191, 64, 163, 158, 129, 243, 215, 251,
    124, 227, 57, 130, 155, 47, 255, 135, 52, 142, 67, 68, 196, 222, 233, 203,
    84, 123, 148, 50, 166, 194, 35, 61, 238, 76, 149, 11, 66, 250, 195, 78,
    8, 46, 161, 102, 40, 217, 36, 178, 118, 91, 162, 73, 109, 139, 209, 37,
    114, 248, 246, 100, 134, 104, 152, 22, 212, 164, 92, 204, 93, 101, 182, 146,
    108, 112, 72, 80, 253, 237, 185, 218, 94, 21, 70, 87, 167, 141, 157, 132,
    144, 216, 171, 0, 140, 188, 211, 10, 247, 228, 88, 5, 184, 179, 69, 6,
    208, 44, 30, 143, 202, 63, 15, 2, 193, 175, 189, 3, 1, 19, 138, 107,
    58, 145, 17, 65, 79, 103, 220, 234, 151, 242, 207, 206, 240, 180, 230, 115,
    150, 172, 116, 34, 231, 173, 53, 133, 226, 249, 55, 232, 28, 117, 223, 110,
    71, 241, 26, 113, 29, 41, 197, 137, 111, 183, 98, 14, 170, 24, 190, 27,
    252, 86, 62, 75, 198, 210, 121, 32, 154, 219, 192, 254, 120, 205, 90, 244,
    31, 221, 168, 51, 136, 7, 199, 49, 177, 18, 16, 89, 39, 128, 236, 95,
    96, 81, 127, 169, 25, 181, 74, 13, 45, 229, 122, 159, 147, 201, 156, 239,
    160, 224, 59, 77, 174, 42, 245, 176, 200, 235, 187, 60, 131, 83, 153, 97,
    23, 43, 4, 126, 186, 119, 214, 38, 225, 105, 20, 99, 85, 33, 12, 125};

int rcon[4][10] = {
    {1, 2, 4, 8, 16, 32, 64, 128, 27, 54},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

int key_schedule[4][4 * (NR + 1)];
int state[4][NB];

void key_expansion(String key)
{
  int temp = key.length();
  if (key.length() < 4 * NK)
  {
    temp = 4 * NK;
  }
  int key_symbols[temp];
  for (int i = 0; i < key.length(); i++)
  {
    key_symbols[i] = key[i];
  }
  if (key.length() < 4 * NK)
  {
    for (int i = key.length(); i < 4 * NK; i++)
    {
      key_symbols[i] = 1;
    }
  }
  for (int row = 0; row < 4; row++)
  {
    for (int col = 0; col < NK; col++)
    {
      key_schedule[row][col] = key_symbols[row + 4 * col];
    }
  }

  for (int col = NK; col < NB * (NR + 1); col++)
  {
    if (col % NK == 0)
    {
      int temp[4];
      for (int row = 0; row < 4; row++)
      {
        temp[row] = key_schedule[(row + 1) % 4][col - 1];
      }
      for (int i = 0; i < 4; i++)
      {
        int sbox_row = temp[i] / 16;
        int sbox_col = temp[i] % 16;
        temp[i] = sbox[16 * sbox_row + sbox_col];
      }
      for (int i = col; i < col + 4; i++)
      {
        int tmp = col / NK - 1;
        key_schedule[i - col][col] = key_schedule[i - col][col - 4] ^ temp[i - col] ^ rcon[i - col][tmp];
      }
    }
    else
    {
      for (int i = col; i < col + 4; i++)
      {
        key_schedule[i - col][col] = key_schedule[i - col][col - 4] ^ key_schedule[i - col][col - 1];
      }
      for (int i = col; i < col + 4; i++)
      {
      }
    }
  }
}

void add_round_key(int rounds)
{
  for (int col = 0; col < NK; col++)
  {
    state[0][col] = state[0][col] ^ key_schedule[0][NB * rounds + col];
    state[1][col] = state[1][col] ^ key_schedule[1][NB * rounds + col];
    state[2][col] = state[2][col] ^ key_schedule[2][NB * rounds + col];
    state[3][col] = state[3][col] ^ key_schedule[3][NB * rounds + col];
  }
}
void sub_bytes(bool inv)
{
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < NB; j++)
    {
      int row = state[i][j] / 16;
      int col = state[i][j] % 16;
      if (inv)
      {
        state[i][j] = inv_sbox[16 * row + col];
      }
      else
      {
        state[i][j] = sbox[16 * row + col];
      }
    }
  }
}

void shift_rows(bool inv)
{
  if (inv)
  {
    for (int i = 1; i < 4; i++)
    {
      int res[NB];
      for (int j = 0; j < NB; j++)
      {
        res[j] = state[i][(j - i + NB) % NB];
      }
      for (int j = 0; j < NB; j++)
      {
        state[i][j] = res[j];
      }
    }
  }
  else
  {
    for (int i = 1; i < 4; i++)
    {
      int res[NB];
      for (int j = 0; j < NB; j++)
      {
        res[j] = state[i][(j + i) % NB];
      }
      for (int j = 0; j < NB; j++)
      {
        state[i][j] = res[j];
      }
    }
  }
}

int mul_by_2(int num)
{
  if (num < 128)
  {
    return (num << 1) % 256;
  }
  else
  {
    return ((num << 1) ^ 27) % 256;
  }
}

int mul(int num, int by)
{
  if (by == 2)
  {
    return mul_by_2(num);
  }
  else if (by == 3)
  {
    return mul_by_2(num) ^ num;
  }
  else if (by == 9)
  {
    return mul_by_2(mul_by_2(mul_by_2(num))) ^ num;
  }
  else if (by == 11)
  {
    return mul_by_2(mul_by_2(mul_by_2(num))) ^ mul_by_2(num) ^ num;
  }
  else if (by == 13)
  {
    return mul_by_2(mul_by_2(mul_by_2(num))) ^ mul_by_2(mul_by_2(num)) ^ num;
  }
  else if (by == 14)
  {
    return mul_by_2(mul_by_2(mul_by_2(num))) ^ mul_by_2(mul_by_2(num)) ^ mul_by_2(num);
  }
}

void mix_columns(bool inv)
{
  for (int i = 0; i < NB; i++)
  {
    int s0, s1, s2, s3;
    if (inv)
    {
      s0 = mul(state[0][i], 14) ^ mul(state[1][i], 11) ^ mul(state[2][i], 13) ^ mul(state[3][i], 9);
      s1 = mul(state[0][i], 9) ^ mul(state[1][i], 14) ^ mul(state[2][i], 11) ^ mul(state[3][i], 13);
      s2 = mul(state[0][i], 13) ^ mul(state[1][i], 9) ^ mul(state[2][i], 14) ^ mul(state[3][i], 11);
      s3 = mul(state[0][i], 11) ^ mul(state[1][i], 13) ^ mul(state[2][i], 9) ^ mul(state[3][i], 14);
    }
    else
    {
      s0 = mul(state[0][i], 2) ^ mul(state[1][i], 3) ^ state[2][i] ^ state[3][i];
      s1 = state[0][i] ^ mul(state[1][i], 2) ^ mul(state[2][i], 3) ^ state[3][i];
      s2 = state[0][i] ^ state[1][i] ^ mul(state[2][i], 2) ^ mul(state[3][i], 3);
      s3 = mul(state[0][i], 3) ^ state[1][i] ^ state[2][i] ^ mul(state[3][i], 2);
    }
    state[0][i] = s0;
    state[1][i] = s1;
    state[2][i] = s2;
    state[3][i] = s3;
  }
}

void encrypt(byte *msg, int msgLen, String key, byte result[17])
{
  int input_byte[msgLen];
  for (int i = 0; i < msgLen; i++)
  {
    input_byte[i] = int(msg[i]);
  }
  for (int row = 0; row < 4; row++)
  {
    for (int col = 0; col < NB; col++)
    {
      state[row][col] = input_byte[row + 4 * col];
    }
  }
  key_expansion(key);

  add_round_key(0);

  for (int rnd = 1; rnd < NR; rnd++)
  {
    sub_bytes(false);
    shift_rows(false);
    mix_columns(false);
    add_round_key(rnd);
  }
  sub_bytes(false);
  shift_rows(false);
  add_round_key(NR);

  String res;
  for (int row = 0; row < 4; row++)
  {
    for (int col = 0; col < NB; col++)
    {
      res.concat(" ");
    }
  }
  for (int row = 0; row < 4; row++)
  {
    for (int col = 0; col < NB; col++)
    {
      res[row + 4 * col] = state[row][col];
    }
  }
  for (int i = 0; i < res.length(); i++)
  {
    int temp = res[i];
  }

  res.concat(" ");
  res.getBytes(result, res.length());
}

void decrypt(byte *ciphertext, int cipherLen, String key, byte result[17])
{
  int cipher[cipherLen];
  for (int i = 0; i < cipherLen; i++)
  {
    cipher[i] = int(ciphertext[i]);
  }
  for (int row = 0; row < 4; row++)
  {
    for (int col = 0; col < NB; col++)
    {
      state[row][col] = cipher[row + 4 * col];
    }
  }
  key_expansion(key);

  add_round_key(NR);

  for (int rnd = NR - 1; rnd > 0; rnd--)
  {
    shift_rows(true);
    sub_bytes(true);
    add_round_key(rnd);
    mix_columns(true);
  }
  shift_rows(true);
  sub_bytes(true);
  add_round_key(0);

  String res;
  for (int row = 0; row < 4; row++)
  {
    for (int col = 0; col < NB; col++)
    {
      res.concat(" ");
    }
  }
  for (int row = 0; row < 4; row++)
  {
    for (int col = 0; col < NB; col++)
    {
      res[row + 4 * col] = state[row][col];
    }
  }
  for (int i = 0; i < res.length(); i++)
  {
    int temp = res[i];
  }
  res.concat(" ");
  res.getBytes(result, res.length());
  // return res;
}