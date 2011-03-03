#!/usr/bin/python

conflist = list()
itemlist = list()

for line in open('tmp.conf', 'r'):
	conflist.append(line[:-1])

for line in open('items.csv', 'r'):
	itemlist.append(line[:-1].split(','))

# 6000-6100
#for i in itemlist:
#	r = i[0].split('-')
#	i.append(str(int(r[1]) - int(r[0])))

conffile = open('./users.conf', 'w')
	
for i in itemlist:				# for csv
	count = int(i[0])
	maxcount = count + int(i[1])
	while count <= maxcount:	#for user range
		insertnum = int(2)
		for n in conflist:		# for conf	
			if(n.find("%s") > -1):
				#print n % i[int(insertnum)]
				conffile.write(n % i[int(insertnum)] + "\n")
				insertnum = int(insertnum) + int(1)
			elif(n.find("%d") > -1):
				#print n % count
				conffile.write(n % count + "\n")
			else:
				#print n
				conffile.write(n + "\n")
		count = count +	1
		#print ""
		conffile.write("\n")

conffile.close()
