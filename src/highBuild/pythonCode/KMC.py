###
#revisions:
#    -Rewrote nested for loop using list comprehension, resulting in less CPU usage and shorter run time.
#    -Fixed "memory leak" issue whereupon data was not overwritten with each iteration of the graph.
#    -In the old code, a graph was generated for every iteration. This is now togglable.
#    -Implemented itertools and gc for optimization purposes
###

import numpy as np
from copy import deepcopy 
import matplotlib.pyplot as plt
import gc #"Garbage collect" tests for uncalled data and deletes it
import itertools as it
from itertools import product      

class Km():
        
    # Euclidean Distance Calculator
    #-----------------------------#
    def dist(a, b, ax = 1):
        return np.linalg.norm(a - b, axis = ax)
    #-----------------------------#
    
    
    # Generate clusters
    #-----------------------------#
    def kmeans(X, k):
        gc.enable()
        
        idx = np.random.randint(len(X), size=k)
        C_1 = X[idx]
        C = np.array(C_1, dtype=np.float32)

        # To store the value of centroids when it updates
        C_old = np.zeros(C.shape)

        # Cluster Labels (0, 1, 2)
        clusters = np.zeros(len(X))

        # This will allow us to collect the path that the centroid takes.
        path = []

        # Error func. - Distance between new centroids and old centroids
        error = Km.dist(C, C_old, None)

        # Loop will run till the error becomes zero
        while error != 0:

            # Assigning each value to its closest cluster
            for i in range(len(X)):

                distances = np.linalg.norm(X[i] - C, axis = 1) # Compute the distance. (Should be k distances here)
                cluster = np.argmin(distances) # Assign the cluster index based on the minimum distance.
                clusters[i] = cluster # Edit the cluster array with the cluster index in the location of the datum in question for the moment in the loop.

            #print(clusters) # Print the clusters for each of the elements of the data set, X.

            # Collect the path info.
            path.append(C_old)

            # Storing the old centroid values.
            C_old = deepcopy(C) 

            #print(C_old) # Print the centroids.

            # Finding the new centroids by taking the average value.
            for i in range(k):
                points = [X[j] for j in range(len(X)) if clusters[j] == i] # Assign points dependent on the cluster index.
                C[i] = np.mean(points, axis=0) # Assign new centroid.

            # Colors for each cluster. We will only have cluster colors up to what we have set here.
            colors = ['r', 'g', 'b', 'y', 'c', 'm']

            # Loop over all the clusters.
            x1 = range(k)
            x2 = range(len(X))
            for i, j in it.product(x1, x2):
                if clusters[j] == i: # Check to see if the cluster index matches the loop index for the outer for loop.
                    points = np.array([X[j]]) # Assign the points for the datum from the list.
                    plt.scatter(points[:, 0], points[:, 1], s= 7, c = colors[i]) # Plot the current state of the data.
            # Assign the current error. While will keep running until the error is zero
            #plt.show() # Show the plot.
            error = Km.dist(C, C_old, None)
        print(clusters,'\n \n',C)
        plt.scatter(C[:, 0], C[:, 1], marker='x', s=200, c='black')
        plt.show()
        Main_list = list(zip(clusters, X))
        WCSS = []
        S = 0
        
        gc.collect()

        for T in Main_list:
            if T[0] == 0:
                S = S + np.log(np.linalg.norm(T[1] -C[0]))

            elif T[0] == 1:
                S = S + np.log(np.linalg.norm(T[1] - C[1]))

            elif T[0] == 2:
                S = S + np.log(np.linalg.norm(T[1] - C[2]))

        return [C, clusters, S]
        plt.show()
    #-----------------------------#
            
    def findclustersize(X , k_max):
        if k_max > 7:
            print("Please choose a smaller k")
        else:
            l = []
            for k in range(1, k_max + 2):
                val = Km.kmeans(X, k)[2]
                l.append([k,val])
                
            plt.axis([0, k_max + 2, 0, int(np.ceil(max(np.array(l)[:,1])))])
            plt.plot(np.array(l)[:,1])
            