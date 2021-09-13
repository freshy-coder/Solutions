input = open('hayfeast.in', 'r')
sum = 0;
maxs = 0;
for i in range (2560) :
  stuff =input.readline().split() 
  sum += int(stuff[0])
  maxs = max(int(stuff[1]), maxs)

print(str(sum) + " and " + str(maxs))