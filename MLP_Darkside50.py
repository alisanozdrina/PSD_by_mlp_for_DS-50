import sys
import numpy as np
import pandas as pd
from sklearn import datasets
#from sklearn import linear_model
#from sklearn.cluster import KMeans
#from sklearn import cross_validation
from sklearn import model_selection
from sklearn import metrics 
from pandas import DataFrame
#from matplotlib import pylab as plt
#from sklearn.ensemble import RandomForestClassifier
from sklearn.externals import joblib as jb
from sklearn.neural_network import MLPClassifier

def MLP(NR, ER, Kr, UAr, output, not_trained):
#Random Forest
    print("----------Multi Layer Perceptron--------------")
    print()
    train_flag=bool(int(not_trained))
    if(train_flag == True):
        print("Using provided datasets for training...")
#input NR data   #x=0 - run_id, x=1 - event_id, x=2 - point from previous event (so drop), x=3-59 -features, x=60,61 - NAN values (so drop)
        NR_data = pd.read_csv(NR, sep = " ", header = None )
        NR_data.drop([60,61], axis = 1, inplace = True) 
        NR_data.columns=["event_id" if x == 1 else x for x in range(60)]  
        target_1 = [1 for x in range(len(NR_data))]
        NR_data['target'] = target_1
        name_1 = ["NR" for x in range(len(NR_data))]
        NR_data['name'] = name_1
        
#input ER data
        ER_data = pd.read_csv(ER, sep = " ", header = None )
        ER_data.drop([60,61], axis = 1, inplace = True)
        ER_data = ER_data[:len(NR_data)] #so that ER and NR will be the same size
        ER_data.columns=["event_id" if x == 1 else x for x in range(60)] #58 is a number of columns
        target_0 = [0 for x in range(len(ER_data))]
        ER_data['target'] = target_0
        name_0 = ['ER' for x in range(len(ER_data))]
        ER_data['name'] = name_0
    
#input Kr data
        Kr_data = pd.read_csv(Kr, sep = " ", header = None )
        Kr_data.drop([60,61], axis = 1, inplace = True)
        Kr_data.columns=["event_id" if x == 1 else x for x in range(60)] #58 is a number of columns
        target_2 = [0 for x in range(len(Kr_data))]
        Kr_data['target'] = target_2
        name_2 = ['Kr' for x in range(len(Kr_data))]
        Kr_data['name'] = name_2
        
        
    #concatenate data together
        frames = [NR_data, ER_data, Kr_data]
        data = pd.concat(frames)
    
    #train-test split
        train_data, test_data, train_labels, test_labels = model_selection.train_test_split(data.iloc[:, 3:60], data['target'], test_size = 0.3, random_state = 0)
    #print(train_data)
    #print(test_data)
    #print(train_labels)
    #print(test_labels)
    
    #train BDT classifier
        from sklearn import datasets, metrics, tree 
    #   clf = tree.DecisionTreeClassifier(random_state=1)
        #clf = RandomForestClassifier(n_estimators = 20,random_state=0)
        clf = MLPClassifier(activation='logistic', random_state=1)
        clf.fit(train_data, train_labels)
    
    #predict
        predictions = clf.predict(test_data)
        print("Accuracy score: " + str(metrics.accuracy_score(test_labels, predictions)))
    
        #features
        #feature_importance = clf.feature_importances_
        #print(feature_importance)
        
        #fig1 = plt.figure()
        #plt.plot([x for x in range(52)],feature_importance,'gs',ms = 4.)
        #plt.show()
        #fig1.savefig("feature_importance.pdf", bbox_inches='tight')
        
        #plot the heatmap
        #import seaborn as sns
        
        #corr = data.iloc[:,3:55].corr()
        #mask = np.zeros_like(corr)
        #mask[np.triu_indices_from(mask)] = True
        #fig, ax = plt.subplots(figsize=(30,30))
        #with sns.axes_style("white"):
        #    ax = sns.heatmap(corr, mask=mask, square=True, cbar=True, annot=True, linewidths=0.5)
        #plt.show()
        #fig.savefig("heatmap.pdf", bbox_inches='tight')
        
        #Output errors
        print("Mean absolute error: " + str(metrics.mean_absolute_error(test_labels, predictions)))
        print("Mean squared error: " + str(metrics.mean_squared_error(test_labels, predictions)))
        print("Precision score: "+ str(metrics.precision_score(test_labels, predictions)))
        print("Recall score: " + str(metrics.recall_score(test_labels, predictions)))
        
        #import graphviz 
        #dot_data = tree.export_graphviz(clf, out_file=None) 
        #graph = graphviz.Source(dot_data) 
        #graph.render("S1_signal_tree_vizualization") 
        
        
        #plt.close("all")
        print("Exporting trained classifier for deployment")
        jb.dump(clf, "mlp_DS50.pkl")
    
        
    clf_trained = jb.load("mlp_DS50.pkl")
    #make a txt to plot the data in root
    UAr_test_data = pd.read_csv(UAr, sep = " ", header = None )
    UAr_test_data_0 = UAr_test_data.drop([2, 60, 61], axis = 1)
    UAr_test_data_0 = UAr_test_data_0.drop([0, 1], axis = 1)
    predictions_UAr = clf_trained.predict(UAr_test_data_0)
    df = pd.DataFrame(predictions_UAr)
    df['run_id'] = UAr_test_data.iloc[:, 0]
    df['event_id'] = UAr_test_data.iloc[:, 1]
    output_name = output + "UAr_MLP_output.txt"
    print("Saving results to "+ output_name)
    df.to_csv(output_name, mode = 'w', header = False, sep = ' ', index_label = False)
    
if __name__ == "__main__":
    NR = sys.argv[1]
    ER = sys.argv[2]
    Kr = sys.argv[3]
    UAr = sys.argv[4]
    output = sys.argv[5]
    not_trained = sys.argv[6]
    MLP(NR, ER, Kr, UAr, output, not_trained)

