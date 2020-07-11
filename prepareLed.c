#include <stdio.h>

#define IMAGE_WIDTH 70
#define IMAGE_HEIGHT 70
#define CSV_FILENAME "img.csv"

typedef struct {
  int r;
  int g;
  int b;
} CRGB;

CRGB img[IMAGE_WIDTH * IMAGE_HEIGHT];

FILE *fp;
// NOTE: Referring to the CSV parsing code in ReadCsv.ino,
// C's equivalent of read(&ch, 1) is fscanf(fp, "%c", &ch)

void loadImage();
void printImage();

int main() {    
  if ((fp = fopen(CSV_FILENAME, "r")) == NULL){
    printf("Error opening file!");
    return 1;
  }

  loadImage();
  printImage();

  return 0;
}

void loadImage() {
  // 70x70 checkerboard
  for (int i = 0; i < IMAGE_WIDTH * IMAGE_HEIGHT; i++) {
    if (i % 2 == 0) {
      img[i].r = 255;
      img[i].g = 255;
      img[i].b = 255;
    } else {
      img[i].r = 0;
      img[i].g = 0;
      img[i].b = 0;
    }
  }
}

void printImage() {
  // Convert to 2D array first, easier to print that way
  CRGB mat[IMAGE_WIDTH][IMAGE_HEIGHT];

  int x = 0, y = 0, dy = 1;
  for (int i = 0; i < IMAGE_WIDTH * IMAGE_HEIGHT; i++) {
    mat[x][y] = img[i];
    
    y += dy;
    if (dy == 1 && y == IMAGE_HEIGHT) {
      x++;
      dy = -1;
      y += dy;
    } else if (dy == -1 && y == -1) {
      x++;
      dy = 1;
      y += dy;
    }
  }

  printf("Image:\n");
  for (y = 0; y < IMAGE_HEIGHT; y++) {
    for (x = 0; x < IMAGE_WIDTH; x++) {
      CRGB pix = mat[x][y];
      if (pix.r == 0 && pix.g == 0 && pix.b == 0) {
        printf("\033[0;40m \033[0;49m");
      } else if (pix.r == 255 && pix.g == 255 && pix.b == 255) {
        printf("\033[0;47m \033[0;49m");
      } else {
        printf("\033[0;41m \033[0;49m");
      }
    }
    printf("\n");
  }
}