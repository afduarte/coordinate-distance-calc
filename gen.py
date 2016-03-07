from random import uniform
from sys import argv

lines = int(argv[1])

def newpoint():
   return uniform(-90, 90), uniform(-180,180)

points = (newpoint() for x in xrange(lines))
for point in points:
   print point
