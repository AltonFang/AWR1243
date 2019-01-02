#include <stdio.h>
#include <assert.h>
void dump_file(char *filename, char *mode);

int main()
{
  FILE *fp;

  dump_file("adc_data03.bin", "rb");
  return 0;
}

void dump_file(char *filename, char *mode)
{
  int c;
  int count = 0;
  FILE *fp = fopen(filename, mode);

  assert(fp != NULL);
  while ((c = fgetc(fp)) != EOF) {
    printf("%02x ", c);
    count++;
    if (count % 16 ==0) {
      putchar('\n');
    }
  }
  fclose(fp);

  printf("\nThere are %d bytes in file %s\n", count, filename);
  return;
}
