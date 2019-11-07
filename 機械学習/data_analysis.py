import numpy as np
import pandas as pd


data=pd.read_table('output.txt',names=["detector_posi","Energy","x_vector","y_vector","dummy1","blank1","dummy2","blank2","dummy3","pla1","dummy4","iron1","dummy5","blank3","dummy6","pla2","dummy7","iron2","dummy8","blank4","dummy9","pla3"],sep=" ")



data=data.fillna(0)
data=data.drop("dummy1",axis=1)
data=data.drop("dummy2",axis=1)
data=data.drop("dummy3",axis=1)
data=data.drop("dummy4",axis=1)
data=data.drop("dummy5",axis=1)
data=data.drop("dummy6",axis=1)
data=data.drop("dummy7",axis=1)
data=data.drop("dummy8",axis=1)
data=data.drop("dummy9",axis=1)
data=data.drop("blank1",axis=1)
data=data.drop("blank2",axis=1)
data=data.drop("blank3",axis=1)
data=data.drop("blank4",axis=1)


data=data[data['detector_posi']>0]

np.savetxt('output3.txt',data,fmt='%.3fi')
