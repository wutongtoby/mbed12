# this program is used to calculate the number of number we have
# to add on 1500 to get specific speed! 

import matplotlib.pyplot as plt
import numpy as np

Ts = 30   # signal interval
end = 150 # signal end point
n = int(end/Ts)+1

x = np.linspace(0, end, num=n) # signal vector

#TODO: revise this array to your results
y = np.array([0.000, 5.423, 9.650, 12.600, 13.238, 13.557]) # speed vector

z = np.polyfit(x, y, 2) # Least squares polynomial fit, and return the coefficients.

goal = 8             # if we want to let the servo run at 7 cm/sec
                     # equation : z[0]*x^2 + z[1]*x + z[2] = goal
z[2] -= goal         # z[0]*x^2 + z[1]*x + z[2] - goal = 0

result = np.roots(z) # Return the roots of a polynomial with coefficients given

# output the correct one, since there will be two root!
# And we alway output the one that is between 0~150(end)
if (0 <= result[0]) and (result[0] <= end):
    print(result[0])
else:
    print(result[1])
