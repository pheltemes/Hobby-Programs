import matplotlib.pyplot as plt 
import numpy as np 

fixed_costs = 13000.0
marginal_cost = 1.0
costs_per_month = 60/7*30+40
cookies_sold_per_month = input("Goal for Number of Cookies sold per month: ")
price = input("Price used for cookies: ")


fig = plt.figure()
fig.patch.set_facecolor('white')

monthly_gains = cookies_sold_per_month*price-cookies_sold_per_month*marginal_cost-costs_per_month
if(monthly_gains > 0):
    intersection_variable_x = 13000/monthly_gains
    s = "Selling " + str(cookies_sold_per_month) + " a month at a price of "+ str(price) + " would take " + str(round(intersection_variable_x)) + " months to break even."
    plt.text(2, 1000, s)
    #Graph of break_even
    x = [intersection_variable_x, intersection_variable_x]
    y = [0,intersection_variable_x*price*cookies_sold_per_month]
    break_even = plt.plot(x,y)
    plt.setp(break_even, label= "break_even")
else:
    intersection_variable_x=20
    s = "Selling " + str(cookies_sold_per_month) + " a month at a price of "+ str(price) + " would never be profitable."
    plt.text(2, 1000, s)

if(monthly_gains > 0):
    intersection_fixed_x = 13000/(price*cookies_sold_per_month)
#revenue_x = [0,13000/4,13000/3,10000] 
revenue_x_months= [0,intersection_variable_x,2*intersection_variable_x] 
revenue_y = [0,intersection_variable_x*price*cookies_sold_per_month,2*intersection_variable_x*price*cookies_sold_per_month]    
revenue = plt.plot(revenue_x_months,revenue_y)
plt.setp(revenue, label = "Revenue") 
#Graph of fixed costs 
#fixed_costs_x_amount = [0,10000]
fixed_costs_x_months = [0,intersection_variable_x,2*intersection_variable_x]
fixed_costs_y = [13000,13000,13000]
fixed_costs = plt.plot(fixed_costs_x_months,fixed_costs_y)
plt.setp(fixed_costs, label= "Dollars")
  
#Graph of variable costs
#x_3 = [0,13000/3,10000]
variable_x_months= [0,intersection_variable_x,intersection_variable_x*2]
variable_y = [13000,13000+intersection_variable_x*(marginal_cost*cookies_sold_per_month+costs_per_month),13000+intersection_variable_x*2*(marginal_cost*cookies_sold_per_month+costs_per_month)]
variable_costs = plt.plot(variable_x_months,variable_y)
plt.setp(variable_costs, label= "Variable Costs")

# naming the x axis 
plt.xlabel('Months') 
# naming the y axis 
plt.ylabel('Fixed Costs') 
  
# giving a title to my graph 
plt.title('Break-Even Analysis') 
  
# function to show the plot 
plt.show() 
