import numpy as np
from keras.models import Sequential
from keras.layers import Dense, Activation
from keras.optimizers import SGD

from sklearn.utils import shuffle

M=2 #入力データの次元
K=3 #クラス数
n=100 #クラス毎のデータ数
N=n*K #全データ数

X1 = np.random.randn(n,M)+np.array([0,10])
X2 = np.random.randn(n,M)+np.array([5,5])
X3 = np.random.randn(n,M)+np.array([10,0])

Y1 = np.array([[1,0,0] for i in range(n)]) 
Y2 = np.array([[0,1,0] for i in range(n)])
Y3 = np.array([[0,0,1] for i in range(n)])

X=np.concatenate((X1,X2,X3), axis=0)#配列の連結
Y=np.concatenate((Y1,Y2,Y3), axis=0)#配列の連結
#X=np.shape(X)
#print(X)

model =Sequential() #層構造の定義
model.add(Dense(input_dim=M,units=K))
model.add(Activation('softmax'))

model.compile(loss='categorical_crossentropy',optimizer=SGD(lr=0.1)) #出力が多クラスの場合はcategorical
minibatch_size =50
model.fit(X,Y,epochs=20,batch_size=minibatch_size)
X_,Y_ =shuffle(X,Y)
classes=model.predict_classes(X_,batch_size=minibatch_size)#0or1or2にぶんるいされる
prob=model.predict_proba(X_,batch_size=1)#10行分の確率を出す
#print(classes)
print('classified:')
print(np.argmax(model.predict(X_),axis=1)==classes)
print()
print('output_probability:')
print(prob)


#print(model.get_weights())
