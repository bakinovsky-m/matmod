import matplotlib.pyplot as plt

x = []
y = []

eps = 1e-3

cookie_temp = 27.0
tea_temp = 100
speed = 0.5
t = 10

counter = 1

prev_temp = cookie_temp

while(counter < t/eps):
	cur_temp = speed*eps*(tea_temp - prev_temp) + prev_temp
	prev_temp = cur_temp
	x.append(counter)
	y.append(cur_temp)
	counter += 1

plt.plot(x, y, '-')
plt.show()