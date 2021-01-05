import numpy as np
import pandas as pd

a = input("Enter the part(b/c) to continue: ")
#print(a)
if a == "b":
	data = pd.read_csv("/home/ritik/Desktop/CN/Assignment2/ping2b.txt",nrows = 99,header = None,sep=' |=', engine = 'python')  #read the data from the ping2.txt file
	data = data[data[5].notna()] #remove all the values that are null
	#print(data)
	data = data[:-1]    # we are accidentally taking the last row, so we need to removeit
	data = data.iloc[1:,[5]].to_numpy()  #converting the values in to numpy array
	#print("SORTED DATA")
	data1 = np.array(sorted(data,key=float)) #sorted the array to calculate the percentile
	#print("Sorted Data")
	len1 = len(data1)   #We need to find the percentile from the total received values
	print("DATA Latency(b)")
	print("Median: " + str(float(data1[int(0.50*len1)-1])))
	print("90 Percentile: " + str(float(data1[int(0.90*len1)-1])))
	print("99 Percentile: " + str(float(data1[int(0.99*len1)-1])))

elif a == "c":
	data = pd.read_csv("/home/ritik/Desktop/CN/Assignment2/ping2c.txt",nrows = 99,header = None,sep=' |=', engine='python')  #read the data
	#print(data)
	data = data[data[5].notna()] #removed the null queries
	data = data[:-1] #dropped the last row
	data = data.iloc[1:,[5]].to_numpy()  #converting the rows to numpy array
	#print("SORTED DATA")
	data2 = np.array(sorted(data,key=float)) #sorting the data
	#print("Sorted Data")
	#print(len(data2))
	len = len(data2) #to calculate the percentile
	print("DATA Latency(c)")
	print("Median: " + str(float(data2[int(len*0.50)-1])))
	print("90 Percentile: " + str(float(data2[int(0.90*len)-1])))
	print("99 Percentile: " + str(float(data2[int(0.99*len)-1])))

else :
	print("Enter valid choice")  #for the invalid choice
