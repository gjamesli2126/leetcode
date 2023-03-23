from openpyxl import Workbook,load_workbook
from copy import deepcopy
from sys import exit
workbook = load_workbook(filename="leetcode_progress.xlsx")
lcprogress = workbook.active

def read_row_val(row):
    Date = lcprogress[f"B{row}"].value
    if Date is not None:
        Date = str(Date).split()[0].replace("-", "/")
    lcnum = lcprogress[f"C{row}"].value
    try:
        times = int(lcprogress[f"E{row}"].value)
    except:
        times=1
    problem = lcprogress[f"D{row}"].value
    alg = lcprogress[f"F{row}"].value
    diff = lcprogress[f"G{row}"].value
    note = lcprogress[f"H{row}"].value
    othdat = lcprogress[f"I{row}"].value
    url = lcprogress[f"J{row}"].value
    return Date,lcnum,times,problem,alg,diff,note,othdat,url
def store_row_val(row,item,val):
    dict1={"Date": "B","lcnum": "C","times" : "E","problem" : "D","alg" : "F","diff" : "G","note" : "H","othdat" : "I","url" : "J"}
    if type(val) is list: # for date update
        val.sort()
        lcprogress[f"{dict1[item]}{row}"].value=', '.join(val)
    else:
        lcprogress[f"{dict1[item]}{row}"].value =val
def find_real_date(row):
    Date=None
    while Date is None:
        row-=1
        Date=read_row_val(row)[0]
    return Date

if __name__ =="__main__":
    #reclac all
    dict0={}
    row=1
    while True:
        row+=1
        packed=read_row_val(row)
        # print(packed)
        if packed==(None,None,1,None,None,None,None,None,None):
            break
        Date, lcnum, times, problem, alg, diff, note, othdat, url = packed

        if Date is None:
            Date=find_real_date(row)

        if lcnum not in dict0.keys():
            dict0[lcnum]=[[Date], 1,[row]]#build hashmap
        else:
            dict0[lcnum][1]+=1 # add times
            dict0[lcnum][0].append(Date) # add oth date
            dict0[lcnum][2].append(row)
    print("Done excel full search!")
    # update excel
    for lcnum,(othdat,times,rows) in dict0.items():
        for row in rows:
            othdat_to_be_store = deepcopy(othdat)
            Date=read_row_val(row)[0]
            if Date is None:
                Date=find_real_date(row)

            othdat_to_be_store.remove(Date)
            # print(othdat_to_be_store,Date)
            store_row_val(row,"othdat",othdat_to_be_store)
            store_row_val(row,"times",times)
    print("Done list update!")
    workbook.save(filename="leetcode_progress.xlsx")
    print("Stored.")