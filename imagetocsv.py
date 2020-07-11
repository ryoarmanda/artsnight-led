from PIL import Image
import csv

img = Image.open('img.png')
pic = img.load()
dim = img.size

with open('img.csv', 'w', newline='') as csvFile:
    fileWriter = csv.writer(csvFile, delimiter=',')
    for x in range(dim[0]):
        if x % 2 == 0:
            lo = 0
            hi = dim[1]
            dir = 1
        else:
            lo = dim[1] - 1
            hi = -1
            dir = -1
        for y in range(lo, hi, dir):
            fileWriter.writerow(pic[x, y])
