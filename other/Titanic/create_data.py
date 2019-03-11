# remove warnings
import warnings
warnings.filterwarnings('ignore')
import pandas as pd
pd.options.display.max_columns = 100
from matplotlib import pyplot as plt
import matplotlib
matplotlib.style.use('ggplot')
import numpy as np
from scipy.stats import mode
from sklearn.ensemble import RandomForestClassifier


data = pd.read_csv('train.csv')
data.shape
#removing irrelevant data
data = data.drop(['Name', 'Ticket', 'Cabin'], axis=1)
# identify missing data : Age + Embark
#print(data.info())
#replace missing ages with median
data['Age'].fillna(data['Age'].median(), inplace=True)
#replace missing Embarked with most frequent value
data['Embarked'].fillna(data['Embarked'].mode()[0], inplace=True)
data = data.dropna()

### DISPLAY CHARTS TO IDENTIFY POTENTIAL
# specifies the parameters of our graphs
fig1 = plt.figure(figsize=(22,8), dpi=100)
alpha_bar_chart = 0.5

# two graphs
ax1 = fig1.add_subplot(211)
# bar graph survived/dead
data.Survived.value_counts().plot(kind='bar', alpha=alpha_bar_chart)
# puts a title
plt.title("Global distribution of Survival")
#graph male female
d_male = data.Survived[data.Sex == 'male'].value_counts().sort_index()
d_female = data.Survived[data.Sex == 'female'].value_counts().sort_index()
ax2 = fig1.add_subplot(212)
d_male.plot(kind='bar', color='#5042f4', label='Male', alpha=0.55)
d_female.plot(kind='bar', color='#ffcc00',label='Female', alpha=0.55)
plt.title("Survival by Gender"); plt.legend(loc='best')
plt.show()

fig2 = plt.figure(figsize=(22,14))
plt.hist([data[data['Survived']==1]['Age'], data[data['Survived']==0]['Age']], stacked=False, color = ['blue','red'],
         bins = 'auto',label = ['Survived','Dead'])
plt.xlabel('Age')
plt.ylabel('Number of passengers')
plt.legend()
plt.show()

fig3 = plt.figure(figsize=(22,14))
plt.hist([data[data['Survived']==1]['Fare'],data[data['Survived']==0]['Fare']], stacked=False, color = ['blue','red'],
         bins = 'auto',label = ['Survived','Dead'])
plt.xlabel('Fare')
plt.ylabel('Number of passengers')
plt.legend()
plt.show()

fig4 = plt.figure(figsize=(22,14))
plt.hist([data[data['Survived']==1]['Pclass'],data[data['Survived']==0]['Pclass']], stacked=False, color = ['blue','red'],
         bins = 'auto',label = ['Survived','Dead'])
plt.xlabel('Class')
plt.ylabel('Number of passengers')
plt.legend()
plt.show()

#train model attemp :
#as Scikit-learn use digit we must transform all strings/chars
data['Gender'] = data['Sex'].map({'female': 0, 'male': 1}).astype(int)
data['Port'] = data['Embarked'].map({'C':1, 'S':2, 'Q':3})
data = data.drop(['Sex', 'Embarked'], axis=1)
cols = data.columns.tolist()
cols = [cols[1]] + cols[0:1] + cols[2:]
data = data[cols]
#print(data.info())

train_data = data.values
model = RandomForestClassifier(n_estimators = 100)
model = model.fit(train_data[0:,2:],train_data[0:,0])

#import of the test file - the file format should be the same as train
data_test = pd.read_csv('test.csv')
#print(data_test.info())
data_test = data_test.drop(['Name', 'Ticket', 'Cabin'], axis=1)
data_test['Age'].fillna(data_test['Age'].median(), inplace=True)
#some Fare values are missing - using mean (could be better tho)
data_test['Fare'].fillna(data_test['Fare'].mean(), inplace=True)
data_test['Sex'] = data_test['Sex'].map({'female': 0, 'male': 1}).astype(int)
data_test['Embarked'] = data_test['Embarked'].map({'C':1, 'S':2, 'Q':3})
#print(data_test.info())
test_data = data_test.values
#print(test_data)
output = model.predict(test_data[:,1:])
#stack of values along their axis
result = np.c_[test_data[:,0].astype(int), output.astype(int)]
data_result = pd.DataFrame(result[:,0:2], columns=['PassengerId', 'Survived'])
#concat result and original dataframe
#frames = [data_test, data_result]
#result = pd.concat(frames)
data_result.to_csv('test_result.csv', index=False)
