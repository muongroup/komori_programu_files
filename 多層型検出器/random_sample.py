import numpy as np



x=np.random.normal(4.173,0.1119,1585)
print(x)
np.savetxt('randomsample.txt',x)
