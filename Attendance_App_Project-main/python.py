print ("Mahabub")
print("It's Really good")
#comment:
#print("It's Really good")
#variable = A container for a variable ( string,integer,float,boolent)
#           A variable behaves as if it was the value it contains
#String:
first_name = "Emon"
food = "khacchi Briani" 
email = "mahabub53@gmail.com"
print(f"Hello {first_name}")
print(f"My like: {food}")
print(f"My Email is: {email}")
#Integer:
age = 25
quentity = 3
print(f"You are {age} years old")
print(f"You are buying {quentity} items")
#Float
price = 10.99
gpa = 3.90
print(f"The price is ${price}")
print(f"The result is {gpa}")
#Boolean
is_student = False
if is_student:
    print("You are a student")
else:
        print("You are NOT a student")
#Typecasting = the proess of converting a variable from one data
#              type to another str(),int(),float(),bool()
name = "Mahabub Hossain Emon"
age = 21
gpa = 3.9
is_student = True
print(type(name))
print(type(age))
print(type(gpa))
print(type(is_student))
age = str(age)
age +="1"
print(age)
#input() = A function that prompts the user to enter data 
#          Returns the entered data as a string 
name = input("What is your name?:")
age = int(input("How old are you?:"))
age = age + 1
print(f"Hello {name}!")
print(f"HAPPY BIRTHDAY!")
print(f"You are {age} Years old.")

#Exercise 1 Rectangle Area calc

length = float(input ("Enter the length: "))
width = float(input ("Enter the width: "))
area = length * width
print(f"The Area is: {area} ")

#Exercise 2 Shopping Cart program

item = input("What item would you like to buy?: ")
price = float(input("What is the price?: "))
quantity = int(input("How many would you like?: "))
total = price * quantity 

print(f"You have bought {quantity}* {item}/s")
print(f"Your total is:${total} taka")



