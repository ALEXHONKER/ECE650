import string
import sys
import math
global count
count=0
dic={}

nodes={}  #{xx_yy:[[xx,yy],count]}
edges=[]  #[[xx,yy],[xx2,yy2]]    
name2num={}  #{xx_yy:count} record the node that has record, use ite COunt
class street:
	def __init__(self):
		self.name=""
		self.setxy=[]
		self.segline=[]
		self.intersec=[]
		self.no={}
	def setsxy(self,temp):
		self.setxy.append(temp)
	def setname(self,na):
		self.name=na
	def addintersec(self,xy):
		self.intersec.append(xy)

# def interc(x1,y1,x2,y2,x3,y3,x4,y4):
# 	interflag=0;
# 	if (x2-x1)==0:
# 		if(x4-x3)!=0:
# 			k2=(y4-y3)/(x4-x3)
# 			b2=y4-k2*x4
# 			maxy=y1
# 			miny=y2
# 			if y2>y1:
# 				maxy=y2
# 				miny=y1
# 			maxy2=y3
# 			miny2=y4
# 			if y4>y3:
# 				maxy2=y4
# 				miny2=y3
# 			maxx=x3
# 			minxx=x4
# 			if x4>x3:
# 				maxx=x4
# 				minxx=x3
# 			xx=x1
# 			yy=k2*xx+b2
# 			if  yy>=miny and yy<=maxy and yy>=miny2 and yy<=maxy2 and xx<=maxx and xx >= minxx:
# 				print x1,y1,x2,y2,x3,y3,x4,y4
# 				print "\n"
# 				interflag=1;
# 		elif x1==x3:
# 			maxy=y2
# 			miny=y1
# 			if y1>y2:
# 				maxy=y1
# 				miny=y2
# 			maxy2=y3
# 			miny2=y4
# 			if y4>y3:
# 				maxy2=y4
# 				miny2=y3
# 			if maxy==miny2 or miny==maxy2:
# 				print x1,y1,x2,y2,x3,y3,x4,y4
# 				print "\n"
# 				interflag=1;

# 	else:
# 		k1=(y2-y1)/(x2-x1)
# 		b1=y2-k1*x2
# 				#if j != (len(coor2)-1):
# 					# x4=coor2[j+1][0]+0.0
# 					# y4=coor2[j+1][1]+0.0
# 		if (x4-x3)==0:
# 			maxy=y1
# 			miny=y2
# 			if y2>y1:
# 				maxy=y2
# 				miny=y1
# 			maxy2=y3
# 			miny2=y4
# 			if y4>y3:
# 				maxy2=y4
# 				miny2=y3
# 			maxx=x1
# 			minxx=x2
# 			if x2>x1:
# 				minxx=x1
# 				maxx=x2
# 			xx=x4
# 			yy=k1*xx+b1
# 			if  yy>=miny and yy<=maxy and yy<=maxy2 and yy>=miny2 and xx<=maxx and xx>=minxx:
# 				print x1,y1,x2,y2,x3,y3,x4,y4
# 				print "\n"
# 				interflag=1;
# 		else:
# 			k2=(y4-y3)/(x4-x3)
# 			b2=y4-k2*x4
# 			if k1!=k2:
# 				maxx=x1
# 				minxx=x2
# 				if x2>x1:
# 					maxx=x2
# 					minxx=x1
# 				maxx2=x3
# 				minxx2=x4
# 				if x4>x3:
# 					maxx2=x4
# 					minxx2=x3
# 				maxy=y1
# 				miny=y2
# 				if y2>y1:
# 					maxy=y2
# 					miny=y1
# 				maxy2=y3
# 				miny2=y4
# 				if y4>y3:
# 					maxy2=y4
# 					miny2=y3
# 				xx=(b2-b1)/(k1-k2)
# 				yy=k1*xx+b1
# 				if xx>=minxx and xx<=maxx and yy>=miny and yy<=maxy and yy<=maxy2 and yy>=miny2 and xx<=maxx2 and xx >= minxx2:
# 					print x1,y1,x2,y2,x3,y3,x4,y4
# 					print "\n"
# 					interflag=1;
# 			else:
# 				if (x1==x3 and y1==y3 ) or (x2==x3 and y2==y3) or (x1==x4 and y1==y4) or (x2==x4 and y2==y4):
# 					print x1,y1,x2,y2,x3,y3,x4,y4
# 					print "\n"
# 					interflag=1;
# 	if interflag==1:
# 		print xx,yy
# 	return interflag

def overlap(x1,y1,x2,y2,x3,y3,x4,y4):
	if x1==x2 and x4==x3 and x3==x1:
		maxy=y2
		miny=y1
		if y1>y2:
			maxy=y1
			miny=y2
		maxy2=y3
		miny2=y4
		if y4>y3:
			maxy=y4
			miny=y3
		if (miny2>=miny and miny2<maxy) or (maxy2<=maxy and maxy2>miny):
			return 1
		return 0
	elif (x1==x2 and x3!=x4) or (x1!=x2 and x3==x4) or (x1==x2 and x3==x4 and x1!=x3):
		return 0
	else:
		#bug exists in last version
		# k2=(y4-y3)/(x4-x3)
		# b2=y4-k2*x4
		# k1=(y2-y1)/(x2-x1)
		# b1=y2-k1*x2
		k2=((y4-y3)+0.0)/((x4-x3)+0.0)
		b2=y4-k2*x4
		k1=((y2-y1)+0.0)/((x2-x1))+0.0
		b1=y2-k1*x2
		if k1==k2 and b1==b2:
			maxy=y2
			miny=y1
			if y1>y2:
				maxy=y1
				miny=y2
			maxy2=y3
			miny2=y4
			if y4>y3:
				maxy2=y4
				miny2=y3
			maxx=x2
			minx=x1
			if x1>x2:
				maxx=x1
				minx=x2
			maxx2=x3
			minx2=x4
			if x4>x3:
				maxx2=x4
				minx2=x3
			if k1!=0:
				if (miny2>=miny and miny2<maxy) or (maxy2<=maxy and maxy2>miny):
					#pointer=1
					return 1
			else:
				if (minx2>=minx and minx2<maxx) or (maxx2<=maxx and maxx2>minx):
					#pointer=1
					return 1
		return 0


def add(strs):
	c1=strs.find("\"",0)
	c2=strs.find("\"",c1+1)
	if c1==-1 or c2==-1:
		sys.stderr.write("Error: Wrong format of street name.\n")
		return 0
	#street_name=strs[c1+1:c2].strip()
	street_name=strs[c1+1:c2]
	if dic.has_key(street_name):
		sys.stderr.write("Error: 'a' specified for a street that already exists.\n")
		return 0
	elif street_name=="":
		sys.stderr.write("Error: Street name should not be empty.\n")
		return 0
	else:	
		strs=strs[c2+1:]
		strs=strs.strip()
		str1= street()
		str1.setname(street_name)
		#START CHANDE
		number_of_cor =0
		while strs.strip() != '':
			p1=strs.find("(")
			p2=strs.find(")")
			comma=strs.find(",")
			if p1==-1 or p2==-1 or comma==-1:
				sys.stderr.write("Error: Wrong format of GPS coordiante.\n")
				return	0
			co1=strs[p1+1:p2]
			strs=strs[p2+1:]
			co1=co1.strip()
			cor=co1.split(",")
			if len(cor)!=2 :
				sys.stderr.write("Error:Wrong format of GPS coordinate.\n")
				return 0
			cor[0]=cor[0].strip()
			cor[1]=cor[1].strip()
			if cor[0].isdigit():
				x1=string.atoi(cor[0])
			elif cor[0][0]=="-":
				if cor[0][1:].strip().isdigit():
					x1=-1*string.atoi(cor[0][1:].strip())
				else :
					sys.stderr.write("Error:Wrong format of GPS coordinate.\n")
					return 0		 
			else :
				sys.stderr.write("Error:Wrong format of GPS coordinate.\n")
				return 0
			if cor[1].isdigit():
				y1=string.atoi(cor[1])
			elif cor[1][0]=="-":
				if cor[1][1:].strip().isdigit():
					y1=-1*string.atoi(cor[1][1:].strip())
				else :
					sys.stderr.write("Error:Wrong format of GPS coordinate.\n")
					return 0		 
			else :
				sys.stderr.write( "Error:Wrong format of GPS coordinate.\n")
				return 0
			par=[x1,y1]
			number_of_cor=number_of_cor+1
			#par.append(x1)
			#par.append(y1)
			pointer=0
			intecflag=0;
			if not (strs.strip() == '' and number_of_cor ==1):

				if number_of_cor>=3:
					x2=str1.setxy[len(str1.setxy)-1][0]	
					y2=str1.setxy[len(str1.setxy)-1][1]	
					coor=str1.setxy
					for i in range(len(coor)):
						if pointer==1 or intecflag==1:
							break
						x3=coor[i][0]+0.0
						y3=coor[i][1]+0.0
						if i != (len(coor)-1):
							x4=coor[i+1][0]+0.0
							y4=coor[i+1][1]+0.0
							#print pointer
							#print x1,y1,x2,y2,x3,y3,x4,y4
							pointer=overlap(x1,y1,x2,y2,x3,y3,x4,y4)
						# if i < (len(coor)-2):
						# 	x4=coor[i+1][0]+0.0
						# 	y4=coor[i+1][1]+0.0
						# 	intecflag=interc(x1+0.0,y1+0.0,x2+0.0,y2+0.0,x3,y3,x4,y4);
					if pointer==0:
						str1.setsxy(par)
					else:
						sys.stderr.write( "Error: Overlap with other line segment in this street.\n")
						return 0
					# if intecflag==1:
					# 	sys.stderr.write(street_name)
					# 	sys.stderr.write( "Error: The street intersects with itself.\n")
					# 	sys.stderr.flush()
					# 	sys.stdout.flush()
					# 	return -1
				elif number_of_cor==2:
					x2=str1.setxy[len(str1.setxy)-1][0]	
					y2=str1.setxy[len(str1.setxy)-1][1]
					if not (x1==x2 and y1==y2):
						str1.setsxy(par)
					else:
						sys.stderr.write( "Error: Wrong coordinates, two same ends in a street.\n")
						return 0
				else:
					str1.setsxy(par)
			else:
				sys.stderr.write("Error: Incomplete coordinates in a \""+str(street_name)+"\", no end point.\n")
				return 0
		pointer =0
		coor=str1.setxy
		for i in range(len(coor)):
			if pointer==1:
				break
			x1=coor[i][0]+0.0
			y1=coor[i][1]+0.0
			if i != (len(coor)-1):
				x2=coor[i+1][0]+0.0
				y2=coor[i+1][1]+0.0
				for nam in dic.keys():
				 	coor2=dic[nam].setxy
				 	if pointer==1:
				 		break
					for j in range(len(coor2)):
						if pointer==1:
							break
						x3=coor2[j][0]+0.0
						y3=coor2[j][1]+0.0
						if j != (len(coor2)-1):
							x4=coor2[j+1][0]+0.0
							y4=coor2[j+1][1]+0.0
							pointer=overlap(x1,y1,x2,y2,x3,y3,x4,y4)


		if pointer ==0:
			dic[street_name]=str1
		else:
			sys.stderr.write( "Error: Overlap with other street.\n")
			return 0

def delete(strs):
	c1=strs.find("\"",0)
	c2=strs.find("\"",c1+1)
	if c1==-1 or c2==-1:
		sys.stderr.write( "Error: Wrong format of street name.\n")
		return
	#street_name=strs[c1+1:c2].strip()
	street_name=strs[c1+1:c2]
	if not dic.has_key(street_name):
		sys.stderr.write( "Error: 'c' specified for a street that does not exit.\n")
		return
	else:
		del dic[street_name]
		add(strs)
		#print dic.keys()
		#print dic[street_name].setxy

def remove(strs):
	c1=strs.find("\"",0)
	c2=strs.find("\"",c1+1)
	if c1==-1 or c2==-1:
		sys.stderr.write( "Error: Wrong format of street name\n")
		return
	#street_name=strs[c1+1:c2].strip()
	street_name=strs[c1+1:c2]
	if not dic.has_key(street_name):
		sys.stderr.write( "Error: 'r' specified for a street that does not exit.\n")
		return
	else:
		del dic[street_name]

def removeall():
	global count
	count=0
	for nam in dic.keys():
		del dic[nam]
	for no in nodes.keys():
		del nodes[no]
	for n in name2num.keys():
		del name2num[n]


def graph():
	global count  # Needed to modify global copy 
	nodes={}
	edges=[]
	str_name=dic.keys()
	for strs in str_name:
		coor=dic[strs].setxy
		#print "Start str:    "+strs
		for i in range(len(coor)):
			x1=coor[i][0]+0.0
			y1=coor[i][1]+0.0
			if i != (len(coor)-1):
				newstr=dic[strs]
				newstr.no={}
				dic[strs]=newstr
				x2=coor[i+1][0]+0.0
				y2=coor[i+1][1]+0.0
				if (x2-x1)==0:
					str_name2 = dic.keys()
					str_name2.remove(strs)
					for strs2 in str_name2:
						coor2=dic[strs2].setxy
						for j in range(len(coor2)):
							x3=coor2[j][0]
							y3=coor2[j][1]
							if j != (len(coor2)-1):
								x4=coor2[j+1][0]+0.0
								y4=coor2[j+1][1]+0.0
								if(x4-x3)!=0:
									k2=(y4-y3)/(x4-x3)
									b2=y4-k2*x4
									maxy=y1
									miny=y2
									if y2>y1:
										maxy=y2
										miny=y1
									maxy2=y3
									miny2=y4
									if y4>y3:
										maxy2=y4
										miny2=y3
									maxx=x3
									minxx=x4
									if x4>x3:
										maxx=x4
										minxx=x3
									xx=x1
									yy=k2*xx+b2
									if  yy>=miny and yy<=maxy and yy>=miny2 and yy<=maxy2 and xx<=maxx and xx >= minxx:
										new_street=dic[strs]
										new_street.addintersec([xx,yy])	
										nidx1y1=str(x1)+'_'+str(y1)
										if not nodes.has_key(nidx1y1):
											if name2num.has_key(nidx1y1):
												pairx1y1=[[x1,y1],name2num[nidx1y1]]
											else:
												pairx1y1=[[x1,y1],count]
												name2num[nidx1y1]=count
												count=count+1
											#print strs2
											nodes[nidx1y1]=pairx1y1
											new_street.no[nidx1y1]=pairx1y1
										else:
											if not new_street.no.has_key(nidx1y1):
												pairx1y1=nodes[nidx1y1]
												new_street.no[nidx1y1]=pairx1y1
												#print "old: "+strs2

										nidx2y2=str(x2)+'_'+str(y2)
										if not nodes.has_key(nidx2y2):
											if name2num.has_key(nidx2y2):
												pairx2y2=[[x2,y2],name2num[nidx2y2]]
											else:
												pairx2y2=[[x2,y2],count]
												name2num[nidx2y2]=count
												count=count+1
											#print strs2
											nodes[nidx2y2]=pairx2y2
											new_street.no[nidx2y2]=pairx2y2
										else:
											if not new_street.no.has_key(nidx2y2):
												pairx2y2=nodes[nidx2y2]
												new_street.no[nidx2y2]=pairx2y2
												#print "old: "+strs2
										if not ((xx==x1 and yy==y1) or (xx==x2 and yy==y2)):
											nid=str(xx)+'_'+str(yy)										
											if not nodes.has_key(nid):
												if name2num.has_key(nid):
													pair=[[xx,yy],name2num[nid]]
												else:
													pair=[[xx,yy],count]											
													name2num[nid]=count
													count=count+1
												#print strs2
												#print xx,yy
												nodes[nid]=pair
												new_street.no[nid]=pair
											else:
												if not new_street.no.has_key(nid):
													pair2=nodes[nid]
													new_street.no[nid]=pair2
												#print ""
												#print "old: "+strs2
												#print xx,yy
										dic[strs]=new_street    # add the intersection node
								elif x1==x3:
									maxy=y2
									miny=y1
									if y1>y2:
										maxy=y1
										miny=y2
									maxy2=y3
									miny2=y4
									if y4>y3:
										maxy2=y4
										miny2=y3
									if maxy==miny2 or miny==maxy2:
										xx=x1	
										if maxy==miny2:
											yy=maxy
										elif miny==maxy2:
											yy=miny
										new_street=dic[strs]
										new_street.addintersec([xx,yy])	
										nidx1y1=str(x1)+'_'+str(y1)
										if not nodes.has_key(nidx1y1):
											if name2num.has_key(nidx1y1):
												pairx1y1=[[x1,y1],name2num[nidx1y1]]
											else:
												pairx1y1=[[x1,y1],count]
												name2num[nidx1y1]=count
												count=count+1
											#print strs2
											nodes[nidx1y1]=pairx1y1
											new_street.no[nidx1y1]=pairx1y1
										else:
											if not new_street.no.has_key(nidx1y1):
												pairx1y1=nodes[nidx1y1]
												new_street.no[nidx1y1]=pairx1y1
												#print "old: "+strs2

										nidx2y2=str(x2)+'_'+str(y2)
										if not nodes.has_key(nidx2y2):
											if name2num.has_key(nidx2y2):
												pairx2y2=[[x2,y2],name2num[nidx2y2]]
											else:
												pairx2y2=[[x2,y2],count]
												name2num[nidx2y2]=count
												count=count+1
											#print strs2
											nodes[nidx2y2]=pairx2y2
											new_street.no[nidx2y2]=pairx2y2
										else:
											if not new_street.no.has_key(nidx2y2):
												pairx2y2=nodes[nidx2y2]
												new_street.no[nidx2y2]=pairx2y2
												#print "old: "+strs2

										if not ((xx==x1 and yy==y1) or (xx==x2 and yy==y2)):
											nid=str(xx)+'_'+str(yy)										
											if not nodes.has_key(nid):
												if name2num.has_key(nid):
													pair=[[xx,yy],name2num[nid]]
												else:
													pair=[[xx,yy],count]											
													name2num[nid]=count
													count=count+1
												nodes[nid]=pair
												new_street.no[nid]=pair
											else:
												if not new_street.no.has_key(nid):
													pair2=nodes[nid]
													new_street.no[nid]=pair2
										dic[strs]=new_street    # add the intersection node
										#print strs
										#print new_street.setxy






					my=y1
					ny=y2
					nidx1y1=str(x1)+'_'+str(y1)
					nidx2y2=str(x2)+'_'+str(y2)
					idmin=nidx2y2
					idmax=nidx1y1
					if y2>y1:
						my=y2
						ny=y1
						idmin=nidx1y1
						idmax=nidx2y2
					list_node=dic[strs].no.keys()
					if not list_node==[]:
						list_node.remove(nidx1y1)
						list_node.remove(nidx2y2)
						#if not list_node==[]:
						list_node.append(idmax)	
						mindis=9999999.0
						minpair=[]
						minid2=idmin
						while list_node!=[]:
							for ns in list_node:
								pair3=dic[strs].no[ns]
								dis=pair3[0][1]-ny
								if dis<mindis:
									mindis=dis
									minpair=pair3
									minid2=ns
							mindis=999999999.0
							edges.append([dic[strs].no[idmin][1],minpair[1]])
							idmin=minid2
							ny=minpair[0][1]
							list_node.remove(minid2)



					

				else:
					k1=(y2-y1)/(x2-x1)
					b1=y2-k1*x2
					str_name2 = dic.keys()
					str_name2.remove(strs)
					for strs2 in str_name2:
						coor2=dic[strs2].setxy
						for j in range(len(coor2)):
							x3=coor2[j][0]+0.0
							y3=coor2[j][1]+0.0
							if j != (len(coor2)-1):
								x4=coor2[j+1][0]+0.0
								y4=coor2[j+1][1]+0.0
								if (x4-x3)==0:
									maxy=y1
									miny=y2
									if y2>y1:
										maxy=y2
										miny=y1
									maxy2=y3
									miny2=y4
									if y4>y3:
										maxy2=y4
										miny2=y3
									maxx=x1
									minxx=x2
									if x2>x1:
										minxx=x1
										maxx=x2
									xx=x4
									yy=k1*xx+b1
									if  yy>=miny and yy<=maxy and yy<=maxy2 and yy>=miny2 and xx<=maxx and xx>=minxx:
										new_street=dic[strs]
										new_street.addintersec([xx,yy])	

										nidx1y1=str(x1)+'_'+str(y1)
										if not nodes.has_key(nidx1y1):
											#print name2num.has_key(nidx1y1)
											if name2num.has_key(nidx1y1):
												pairx1y1=[[x1,y1],name2num[nidx1y1]]
												#print pairx1y1
											else:
												pairx1y1=[[x1,y1],count]
												name2num[nidx1y1]=count
												count=count+1
											nodes[nidx1y1]=pairx1y1
											#print nodes
											#print strs2
											new_street.no[nidx1y1]=pairx1y1
										else:
											if not new_street.no.has_key(nidx1y1):
												pairx1y1=nodes[nidx1y1]
												new_street.no[nidx1y1]=pairx1y1
												#print "old: "+strs2

										#print "2"
										#print nidx2y2
										#print nodes.has_key(nidx2y2)
										nidx2y2=str(x2)+'_'+str(y2)
										if not nodes.has_key(nidx2y2):
											#print "yes"
											if name2num.has_key(nidx2y2):
												#print "yes2"
												#print nidx2y2
												pairx2y2=[[x2,y2],name2num[nidx2y2]]
												#print pairx2y2
											else:
												pairx2y2=[[x2,y2],count]
												name2num[nidx2y2]=count
												count=count+1
											#print strs2
											nodes[nidx2y2]=pairx2y2
											new_street.no[nidx2y2]=pairx2y2
										else:
											if not new_street.no.has_key(nidx2y2):
												pairx2y2=nodes[nidx2y2]
												new_street.no[nidx2y2]=pairx2y2
												#print "old: "+strs2

										#print "3"
										#print nid
										#print nodes.has_key(nid)
										if not ((xx==x1 and yy==y1) or (xx==x2 and yy==y2)):
											nid=str(xx)+'_'+str(yy)										
											if not nodes.has_key(nid):
												if name2num.has_key(nid):
													pair=[[xx,yy],name2num[nid]]
												else:	
													pair=[[xx,yy],count]
													name2num[nid]=count
													count=count+1
												nodes[nid]=pair
												new_street.no[nid]=pair
											else:
												if not new_street.no.has_key(nid):
													pair2=nodes[nid]
													new_street.no[nid]=pair2
						
										dic[strs]=new_street    # add the intersection node
										#print strs
										#print new_street.setxy

								else:
									k2=(y4-y3)/(x4-x3)
									b2=y4-k2*x4
									if k1!=k2:
										maxx=x1
										minxx=x2
										if x2>x1:
											maxx=x2
											minxx=x1
										maxx2=x3
										minxx2=x4
										if x4>x3:
											maxx2=x4
											minxx2=x3
										maxy=y1
										miny=y2
										if y2>y1:
											maxy=y2
											miny=y1
										maxy2=y3
										miny2=y4
										if y4>y3:
											maxy2=y4
											miny2=y3
										xx=(b2-b1)/(k1-k2)
										yy=k1*xx+b1
										if xx>=minxx and xx<=maxx and yy>=miny and yy<=maxy and yy<=maxy2 and yy>=miny2 and xx<=maxx2 and xx >= minxx2:
											new_street=dic[strs]
											new_street.addintersec([xx,yy])	

											nidx1y1=str(x1)+'_'+str(y1)
											if not nodes.has_key(nidx1y1):
												if name2num.has_key(nidx1y1):
													pairx1y1=[[x1,y1],name2num[nidx1y1]]
												else:
													pairx1y1=[[x1,y1],count]
													name2num[nidx1y1]=count
													count=count+1
												#print strs2
												nodes[nidx1y1]=pairx1y1
												new_street.no[nidx1y1]=pairx1y1
											else:
												if not new_street.no.has_key(nidx1y1):
													pairx1y1=nodes[nidx1y1]
													new_street.no[nidx1y1]=pairx1y1
													#print "old: "+strs2


											nidx2y2=str(x2)+'_'+str(y2)
											if not nodes.has_key(nidx2y2):
												if name2num.has_key(nidx2y2):
													pairx2y2=[[x2,y2],name2num[nidx2y2]]
												else:
													pairx2y2=[[x2,y2],count]
													name2num[nidx2y2]=count
													count=count+1
												nodes[nidx2y2]=pairx2y2
												#print strs2
												new_street.no[nidx2y2]=pairx2y2
											else:
												if not new_street.no.has_key(nidx2y2):
													pairx2y2=nodes[nidx2y2]
													new_street.no[nidx2y2]=pairx2y2
													#print "old: "+strs2
											if not ((xx==x1 and yy==y1) or (xx==x2 and yy==y2)):
												nid=str(xx)+'_'+str(yy)										
												if not nodes.has_key(nid):
													if name2num.has_key(nid):
														pair=[[xx,yy],name2num[nid]]
													else:
														pair=[[xx,yy],count]
														name2num[nid]=count
														count=count+1
													nodes[nid]=pair
													new_street.no[nid]=pair
												else:
													if not new_street.no.has_key(nid):
														pair2=nodes[nid]
														new_street.no[nid]=pair2
											#dic[strs]=new_street    # add the intersection node
											dic[strs]=new_street    # add the intersection node
											#print strs
											#print new_street.setxy
											#print "==================="
											#print dic[strs].no
									else:
										if (x1==x3 and y1==y3 ) or (x2==x3 and y2==y3) or (x1==x4 and y1==y4) or (x2==x4 and y2==y4):
											new_street=dic[strs]
											nidx1y1=str(x1)+'_'+str(y1)
											if not nodes.has_key(nidx1y1):
												#print "sss"
												if name2num.has_key(nidx1y1):
													pairx1y1=[[x1,y1],name2num[nidx1y1]]
												else:
													pairx1y1=[[x1,y1],count]
													name2num[nidx1y1]=count
													count=count+1
												#print strs2
												nodes[nidx1y1]=pairx1y1
												new_street.no[nidx1y1]=pairx1y1
											else:
												if not new_street.no.has_key(nidx1y1):
													pairx1y1=nodes[nidx1y1]
													new_street.no[nidx1y1]=pairx1y1
													#print "old: "+strs2


											nidx2y2=str(x2)+'_'+str(y2)
											if not nodes.has_key(nidx2y2):
												if name2num.has_key(nidx2y2):
													pairx2y2=[[x2,y2],name2num[nidx2y2]]
												else:
													pairx2y2=[[x2,y2],count]
													name2num[nidx2y2]=count
													count=count+1
												nodes[nidx2y2]=pairx2y2
												#print strs2
												new_street.no[nidx2y2]=pairx2y2
											else:
												if not new_street.no.has_key(nidx2y2):
													pairx2y2=nodes[nidx2y2]
													new_street.no[nidx2y2]=pairx2y2
											dic[strs]=new_street
											
					mx1=x1
					my1=y1
					nidx1y1=str(x1)+'_'+str(y1)
					nidx2y2=str(x2)+'_'+str(y2)
					idmin=nidx1y1
					idmax=nidx2y2
					list_node=dic[strs].no.keys()
					if not list_node==[]:
						list_node.remove(nidx1y1)
						list_node.remove(nidx2y2)
						#if not list_node==[]:
						list_node.append(idmax)	
						mindis=9999999.0
						minpair=[]
						minid2=""
						while list_node!=[]:
							for ns in list_node:
								#print "ns: "+ns
								pair3=dic[strs].no[ns]
								dis=math.sqrt((pair3[0][1]-my1)**2+(pair3[0][0]-mx1)**2)
								if dis<mindis:
									mindis=dis
									minpair=pair3
									minid2=ns
								#print "minid2"+minid2
							mindis=99999999.0
							edges.append([dic[strs].no[idmin][1],minpair[1]])
							idmin=minid2
							ny=minpair[0][1]
							#print minid2
							if minid2!="":
								list_node.remove(minid2)
	
	#pipesize=0							#print list_node
	sys.stdout.write("V = ")
	#sys.stdout.flush()
	sys.stdout.write(str(len(nodes)))
	#sys.stdout.flush()
	sys.stdout.write("\n")

	#sys.stdout.flush()
	# listed_nodes={}
	# #print nodes
	# for v in nodes.keys():
	# 	listed_nodes[nodes[v][1]]=nodes[v][0]
	# for v in sorted(listed_nodes):
	# 	sys.stdout.write(str(v)+": (")
	# 	if listed_nodes[v][0]%1==0:
	# 		sys.stdout.write(str(int(listed_nodes[v][0])))
	# 	else:
	# 		sys.stdout.write(str(round(listed_nodes[v][0],2)))
	# 		#sys.stdout.write(str("%.2f" % listed_nodes[v][0]))
	# 	sys.stdout.write(",")
	# 	if listed_nodes[v][1]%1==0:
	# 		sys.stdout.write(str(int(listed_nodes[v][1])))
	# 	else:
	# 		sys.stdout.write(str(round(listed_nodes[v][1],2)))
	# 		#sys.stdout.write(str("%.2f" % listed_nodes[v][1]))
	# 	sys.stdout.write(")")
	# 	sys.stdout.write("\n")
	# sys.stdout.write("\n")
	sys.stdout.write("E = {")
	#pipesize=pipesize+10+len(str(len(nodes)))
	#sys.stdout.flush()
	for i in range(len(edges)):
		edge0=edges[i]
		sys.stdout.write("<"+str(edge0[0])+","+str(edge0[1])+">")
		#pipesize=pipesize
		if ((i+0.0)/(300.0))%1==0.0:
			sys.stdout.flush()
		#sys.stdout.flush()
		if i!=len(edges)-1:
			sys.stdout.write(",")
			#sys.stdout.flush()
		#sys.stdout.write("\n")
	sys.stdout.write("}\n")
	#sys.stdout.flush()


	#print edges
	#print nodes

			
try:
	count=0
	while True:
		# f = open('workfile', 'w')
		# f.write("stdin")
		# f.close
		# cccc=1
		# while True:
		# 	cccc=cccc+1
		# 	line=sys.stdin.readline()
		# 	if not line:
		# 		break
		# 	sys.stdout.write(line)
		# 	sys.stdout.flush()
		# break
		############################################stdin=sys.stdin.readlines()
		stdin=sys.stdin.readline()
		# f = open('workfile2', 'w')
		# f.write("stdin2")
		# f.close
		if not stdin:
			break
		#a= "a \"ws\" (2,-1) (2,2) (5,5) (5,6) (3,8)"
		#for i in range(len(stdin)):
		a=stdin
		a=a.strip()
		# sys.stderr.write("eeeeee:")
		# sys.stderr.write(str(len(a)))
		# sys.stderr.write(a)
		# sys.stderr.write("\n")
		if a=='':
			sys.stderr.write("Error: Please input valid data\n")
		else:
			first=a[0]
			# sys.stderr.write("first:"+first)
			# sys.stderr.write("\n")
			if first=='a' and (a[1]==" " or a[1]=="\""):
				if add(a)== -1: 
					break
			elif first=='c' and (a[1]==" " or a[1]=="\""):
				delete(a)
			elif (first=='r' or (len(a)>1 and a[1]=='r')) and len(a)<=4: #<=5
				removeall()
			elif first=='r' and (a[1]==" " or a[1]=="\""):
				remove(a)
			elif first=='g':
				#count=1
				#print "count"
				#print count
				graph()
				sys.stdout.flush()
				#removeall() # remove all
				# str_name=dic.keys()
			else:
				continue
				#sys.stderr.write(a);
				#sys.stderr.write("Error: Please input valid data_\n")
except KeyboardInterrupt:
    sys.stdout.flush()
    pass