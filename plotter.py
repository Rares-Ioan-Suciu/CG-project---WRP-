import pandas as pd
import matplotlib.pyplot as plt
import os

discrt_met = ["simple", "midpoints", "barycentric", "barycentricWeight", "densityWeight"]

# THIS python script we use to plot the data obtained from the experimetns done with the computation part and the other python script used
# for centralziaing the experiment part and the visualization. THe code should output 4*3 = 12 plots
# 4 for shortest path vs no
# 4 for mem vs no
# 4 for Dijsktra vs A* 
def shortepathVSno(data, point_type): 
    plt.figure(figsize=(10, 6)) # for each of the methods to discretize we gather the data regarding the shortest path lenght from the csv files and, considering the point type
    # we generate a plot line for each method, and a plot for each point type
    for method in discrt_met:
        method_data = data[data["Disct"] == method]  
        if not method_data.empty:
            plt.plot(method_data["No. of points"], method_data["Shortest path"], label=method)
    plt.xlabel("Number of Points")
    plt.ylabel("Shortest Path")
    plt.title(f"{point_type}: Number of Points vs Length of Shortest Path")
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.show()

def mem_usedVSno(data, point_type):
    plt.figure(figsize=(10, 6))
    for method in discrt_met:
        method_data = data[data["Disct"] == method] 
        if not method_data.empty:# for each of the methods to discretize we gather the data regarding the memory usage from the csv files and, considering the point type
    # we generate a plot line for each method, and a plot for each point type
            plt.plot(method_data["No. of points"], method_data["Mem. used"], label=method)
    plt.xlabel("Number of Points")
    plt.ylabel("Memory Used")
    plt.title(f"{point_type}: Number of Points vs Memory Used")
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.show()

def DijsktraVSastar(all_data, point_type):
   
    plt.figure(figsize=(10, 6))
    dijkstra_info = all_data[all_data["Algorithm"] == "dijkstra"]
    if dijkstra_info.empty:
        print(f"No Dijkstra data for {point_type}") 
    else: # we gather from the csv file the data regarding the dijsktra running time, crating a graph line for each of the discretization methods
        for method in discrt_met:
            method_data = dijkstra_info[dijkstra_info["Disct"] == method]
            if not method_data.empty:
                plt.plot(method_data["No. of points"], method_data["Milliseconds"], label=f"Dijkstra - {method}", marker='o')


    astar_info = all_data[all_data["Algorithm"] == "astar"]
    if astar_info.empty:
        print(f"No A* data for {point_type}")
    else:
        for method in discrt_met:
            method_data = astar_info[astar_info["Disct"] == method]
            if not method_data.empty:
                plt.plot(method_data["No. of points"], method_data["Milliseconds"], label=f"A* - {method}", marker='x')


    plt.xlabel("Number of Points")
    plt.ylabel("Milliseconds")
    plt.title(f"Dijkstra VS A*{point_type} - Time vs Number of Points")
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.show()


def plotter(file_directory):
    all_files = [f for f in os.listdir(file_directory) if f.endswith('.csv')]
    point_types = ["random_simple", "random_skewed", "random_boundary_points", "random_cluster"]
    grouped_files = {point_type: [] for point_type in point_types}

    for file in all_files: # we gahter all the files from the directory and group them depeding on the point type, as we will do the plots depeding on that
        for point_type in point_types:
            if file.startswith(point_type):
                grouped_files[point_type].append(os.path.join(file_directory, file))

    for point_type, files in grouped_files.items():
        combined_data = pd.DataFrame()

        for file in files:
            # we deefine the column names that the CSV file will use and read the convert the data into lists to use later
            column_names = ["No. of points", "Mem. used", "Shortest path", "Milliseconds", "Disct", "Algorithm"]
            data = pd.read_csv(file, names=column_names)
            data["No. of points"] = data["No. of points"].astype(int)
            data["Shortest path"] = pd.to_numeric(data["Shortest path"], errors='coerce')
            data["Mem. used"] = pd.to_numeric(data["Mem. used"], errors='coerce')
            data["Milliseconds"] = data["Milliseconds"].replace(r' ms', '', regex=True).astype(float)
            if "dijkstra" in file:
                data["Algorithm"] = "dijkstra"
            elif "astar" in file:
                data["Algorithm"] = "astar"
            for method in discrt_met:
                if method in file:
                    data["Disct"] = method
            
            # Append the data from the current file to the combined_data DataFrame
            combined_data = pd.concat([combined_data, data], ignore_index=True)

        # we will only use the dijkstra files for plotting in the case of shortest path and mem used, this doesn t affect the result as this depend solehy on the discretization methods
        dijkstra_data = combined_data[combined_data["Algorithm"] == "dijkstra"]

        shortepathVSno(dijkstra_data, point_type)
        mem_usedVSno(dijkstra_data, point_type)
        DijsktraVSastar(combined_data, point_type) # actually finally and for the end of it call the plotting fucnrtions


data_dir = "/home/rares655/test_project/cmake-build-debug/" #PLEASE change this if you try to run on you computer, in order to select correct folder for fetching the data
plotter(data_dir)
