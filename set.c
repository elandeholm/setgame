#include <stdio.h>
#include <stdlib.h>

typedef struct
{
  int a, b, c, d;
} card_t;

typedef struct
{
  int i1, i2, i3; 
} triplet_t;

void draw(card_t *_c, int N)
{
  static unsigned int A = 0x93C467E3, B = 0x7DB0C7A4, C = 0xD1BE3F81, D = 0x0152CB56;
  unsigned int a, b, c, d;
  int i;

  for(i = 0; i < N; ++i)
  {
    do
    {
      D ^= (A + B + B);
      A ^= (D + C + C);
      B ^= (C | (D + D));
      C ^= (B + A + i);

      a = (A >> 5) & 255;
      b = (B >> 6) & 255;
      c = (C >> 7) & 255;
      d = (D >> 8) & 255;

      A += b;
      B += a;
      C += d;
      D += c;
    } while(a > 242 || b > 242 || c > 242 || d > 242);

    _c[i].a = a % 3;
    _c[i].b = b % 3;
    _c[i].c = c % 3;
    _c[i].d = d % 3;
  }
}

triplet_t *make_ctable(int N, int *l)
{
  int a, b, c;
  int tlen;
  triplet_t *ct, *ctp;

  *l = N * (N - 1) * (N - 2) / (3 * 2 * 1);

  ct = malloc(sizeof(triplet_t) * *l);
  ctp = ct;

  for(a = 0; a < N; ++a)
  {
    for(b = a + 1; b < N; ++b)
    {
      for(c = b + 1; c < N; ++c)
      {
        ctp->i1 = a;
        ctp->i2 = b;
        ctp->i3 = c;
        ++ctp;
      }
    }
  }

  return ct;
}

int find(int N, unsigned long K)
{
  triplet_t *ct;
  int i, j, k1, k2, k3, l;
  card_t *c, *c1, *c2, *c3;
  int is_set, matched = 0;

  ct = make_ctable(N, &l);

  c = malloc(sizeof(card_t) * N);

  for(i = 0; i < K; ++i)
  {
    draw(c, N);

    is_set = 0;

    for(j = 0; j < l; ++j)
    {
      k1 = ct[j].i1;
      k2 = ct[j].i2;
      k3 = ct[j].i3;

      c1 = &c[k1];
      c2 = &c[k2];
      c3 = &c[k3];

      if (((c1->a == c2->a) && (c1->a == c3->a)) ||
          ((c1->a != c2->a) && (c1->a != c3->a) && (c2->a != c3->a)))
      {
        if (((c1->b == c2->b) && (c1->b == c3->b)) ||
            ((c1->b != c2->b) && (c1->b != c3->b) && (c2->b != c3->b)))
        {
          if (((c1->c == c2->c) && (c1->c == c3->c)) ||
              ((c1->c != c2->c) && (c1->c != c3->c) && (c2->c != c3->c)))
          {
            if (((c1->d == c2->d) && (c1->d == c3->d)) ||
                ((c1->d != c2->d) && (c1->d != c3->d) && (c2->d != c3->d)))
            {
              is_set = 1;
            }
          }
        }
      }

      if (is_set)
      {
        break;
      }
    }

    if (is_set)
    {
      ++matched;
    }
  }

  return matched;
}

int main(int argc, char **argv)
{
  int N, K = 10000000;
  int matched;

  for (N=3; N <= 12; ++N)
  {
    matched = find(N, K);
    printf("N=%d, matched=%d/%d\n", N, matched, K);
  }

  return 0;
}
