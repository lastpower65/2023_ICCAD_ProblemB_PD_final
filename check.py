hash_table = {}

def store_number(string):
    key = string.split(' ')[1][1:]
    hash_table[key] = True

def check_number(number):
    return number in hash_table
file_name = "Bottom_tech_ProblemB_case1_0522.txt"
# 从文件中逐行读取数据并存储数字
with open(file_name, "r") as file:
    for line in file:
        first_element = line.split(' ')[0]
        # print(first_element)
        if(first_element=="Inst"):
            store_number(line.strip())
with open(file_name, "r") as file:
    count_success = 0
    count_fail = 0
    for line in file:
        if(line.find("Pin C") == -1):
            continue
        first_element = line.split(' ')[0]
        if(first_element == "Pin"):
            pin = line.split(' ')[1]
            # print(pin) 
        if(first_element == "Pin"):
            number = pin[1:pin.index('/')]
            if check_number(number):
                count_success += 1
            else:
                count_fail+=1
                print("fail")
                print(number)
print(count_fail)
print(count_success)

# 检查数字是否存在
# number = input("请输入一个数字: ")
# if check_number(number):
#     print("数字存在于之前的数字中。")
# else:
#     print("数字不存在于之前的数字中。")