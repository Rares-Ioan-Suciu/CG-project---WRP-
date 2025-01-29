import os
import subprocess
import tkinter as tk
from tkinter import filedialog, messagebox
import matplotlib.pyplot as plt
from matplotlib.tri import Triangulation
import numpy as np

# as it is explained in the paper this python script will only handle the commands for the framework and the visualization
#the actual computaiton,  creating triangualtions, discretization and shortest paths are handled by the c++ code
#make sure you compile that program and link the correct executbale down here:
the_computing_program = "/home/rares655/test_project/build/delaunay" #PLEASE CHANGE WITH YOUR EXECUTBALE DEAR USER

def work_the_computation_viz(mode, argument):
    try:
        command = [the_computing_program, "visualization" , mode, str(argument)] # here is for doing the viz of the paths
        subprocess.run(command, check=True)
        messagebox.showinfo("All done", f"Everything done. You can visualize file triangulatioAndWay.")
    except subprocess.CalledProcessError as e:
        messagebox.showerror("Error", f"Something really bad happened\n{e}")

def get_file_for_viz():
    path_to_file = filedialog.askopenfilename(title="Please select a file to visualize")
    if path_to_file:
        work_the_computation_viz("input", path_to_file)

def get_No_points(mode, getNum):
    No_points = getNum.get()
    if No_points.isdigit() and int(No_points) > 0:
        work_the_computation_viz(mode, No_points)
    else:
        messagebox.showwarning("Invalid Input", "Please enter an integer number bigger than 0")

def direct_input():
    trig_file = filedialog.askopenfilename(title="Please provide a file with triangulations")
    if trig_file:
        work_the_computation_viz("directly", trig_file)

def parser_viz(viz_file):
    triangle_faces = []
    faces_weights = []
    paths = [] 

    with open(viz_file, 'r') as visualization_file:
        lines = visualization_file.readlines()
        triangles_part = True
        building_path = [] # the vizualization file contains both the triangle faces with their weights and the paths 
        #depending on what part we are on, we either read the triangles or the paths and save the data for later use
        shortest_distances = dict()
        count  = 0
        for line in lines:
            line = line.strip()
            if line.startswith("Triangles:"):
                continue
            elif line.startswith("Shortest path"):
                triangles_part = False
                if building_path:
                    paths.append(building_path)
                building_path = []
                continue
            elif line.startswith("Total distance"):
                count = count +1 
                shortest_distances[count] = float(line.split(":")[1])
                if building_path:
                    paths.append(building_path)
                building_path = []
                continue

            if triangles_part:
                splitted = line.split()
                xCoordonates = [float(splitted[i]) for i in range(0, len(splitted)-1, 2)]
                yCoordonates = [float(splitted[i+1]) for i in range(0, len(splitted)-1, 2)]
                triangle_weight = float(splitted[-1])
                triangle_faces.append((xCoordonates, yCoordonates))
                faces_weights.append(triangle_weight)
            else:
                path_points = line.split()
                for i in range(0, len(path_points), 2):
                    x_coordonate = float(path_points[i])
                    y_coordonate = float(path_points[i+1])
                    building_path.append((x_coordonate, y_coordonate))

        if building_path:
            paths.append(building_path)

    
    while len(paths) < 5: # paths list will always have 5 components, one for each disct. method
        paths.append([]) # if onw of them will be missing we just jump over it 
   
    sorted_distances = sorted(shortest_distances.items(), key=lambda item: item[1])

    print("Methods sorted by shortest distance:")
    for method, distance in sorted_distances:
        if(method == 1):
            print(f"Simple: {distance}")
        if(method == 2):
            print(f"Midpoints + center: {distance}")
        if(method == 3):
            print(f"Barycenter: {distance}")
        if(method == 4):
            print(f"Weighted Barycenter: {distance}")
        if(method == 5):
            print(f"Density: {distance}")
    return triangle_faces, faces_weights, paths[0], paths[1], paths[2], paths[3], paths[4]


def path_plotter(current_path, coloring_path, coloring_mark, title, color_dots): 
       
        if current_path:
            x_coordonates = [p[0] for p in current_path] 
            y_coordonates = [p[1] for p in current_path]
            plt.plot(x_coordonates, y_coordonates, color=coloring_path, linewidth=4, label=title)
            plt.scatter(x_coordonates[0], y_coordonates[0], color=coloring_mark, s=200, zorder=5, marker='*')  
            plt.scatter(x_coordonates[-1], y_coordonates[-1], color=coloring_mark, s=200, zorder=5, marker='D')  
            plt.scatter(x_coordonates[1:-1], y_coordonates[1:-1], color=color_dots, s=50, zorder=5, marker='x') 

def triangulation_path_viz(triangles, weights, simple, midpoints, bary, baryW, density):
    
    x_Coordonates = []
    y_Coordonates = []
    triangle_indices = []
    triangles_weight = []
    # in this fucntion we take every path given separete the x from y and plot each one using the fucntion path_plotter, in
    # order to see how every discretization method offers a different path
    for i, (coords_x, coords_y) in enumerate(triangles):
        for x, y in zip(coords_x, coords_y):
            x_Coordonates.append(x)
            y_Coordonates.append(y)
        triangle_indices.append([len(x_Coordonates) - 3, len(x_Coordonates) - 2, len(x_Coordonates) - 1])
        triangles_weight.append(weights[i])

    trig = Triangulation(x_Coordonates, y_Coordonates, np.array(triangle_indices))
    normal_face_weights = (triangles_weight - np.min(triangles_weight)) / (np.max(triangles_weight) - np.min(triangles_weight))

    plt.figure(figsize=(12, 10))
    plt.tripcolor(trig, facecolors=normal_face_weights, cmap='coolwarm', edgecolors='k', alpha=0.6)

    path_plotter(simple, "darkblue", "lightgreen", "Simple Path", "orange")
    path_plotter(midpoints, "darkviolet", "lightcyan", "Mid/Center Path", "darkgreen")
    path_plotter(bary, "gold", "purple", "Barycentric", "darkred")
    path_plotter(baryW, "deeppink", "lightyellow", "Barycentric Weighted", "darkblue")
    path_plotter(density, "forestgreen", "lightpink", "Density", "goldenrod")
  
    sm = plt.cm.ScalarMappable(cmap='coolwarm', norm=plt.Normalize(vmin=np.min(triangles_weight), vmax=np.max(triangles_weight)))
    sm.set_array([])
    plt.colorbar(sm, label="Weight Axis")

    plt.title("Shortest paths in action", fontsize=20)
    plt.xlabel("X Coordinate", fontsize=10)
    plt.ylabel("Y Coordinate", fontsize=10)
    plt.legend(loc='best', fontsize=12)
    plt.grid(True, linestyle='--', linewidth=1)
    plt.axis("equal")
    plt.show()

def select_paths(triangle_faces, triangles_weights, simple, midpoints, bary, baryW, density):
                sel_window = tk.Toplevel(stage)
                sel_window.title("Discretization methods")
# this fucntion opens the visualziaton file and asks what paths the users wants to see, by using checkboxes in order to give the user the chance 
#to differentiate between paths, without having to generate 5 different plots for each discretization method
                tk.Label(sel_window, text="What paths you want to see?").pack(pady=5)
                simple_check = tk.BooleanVar(value=False)
                mid_check = tk.BooleanVar(value=False)
                bary_check = tk.BooleanVar(value=False)
                baryW_check = tk.BooleanVar(value=False)
                density_check = tk.BooleanVar(value=False)
                tk.Checkbutton(sel_window, text="Simple disct.", variable=simple_check).pack(anchor="w")
                tk.Checkbutton(sel_window, text="Midpoints+Centorid disct.", variable=mid_check).pack(anchor="w")
                tk.Checkbutton(sel_window, text="Barycentric random disct.", variable=bary_check).pack(anchor="w")
                tk.Checkbutton(sel_window, text="Barycentric Weighted disct.", variable=baryW_check).pack(anchor="w")
                tk.Checkbutton(sel_window, text="Density disct.", variable = density_check).pack(anchor="w")

                def apply_selection():
                    sel_simple = simple if simple_check.get() else []
                    sel_midpoints = midpoints if mid_check.get() else []
                    sel_barycentric = bary if bary_check.get() else []
                    sel_baryW = baryW if baryW_check.get() else []
                    sel_density = density if density_check.get() else []
                    sel_window.destroy()
                    triangulation_path_viz(triangle_faces, triangles_weights, sel_simple, sel_midpoints, sel_barycentric, sel_baryW, sel_density)
                tk.Button(sel_window, text="See the paths and the terrain", command=apply_selection).pack(pady=10)


def visualize_start():
    viz_file = filedialog.askopenfilename(title="Please select the file that you want to create the visualziation from")
    if viz_file:  
        try:
            triangle_faces, triangles_weights, simple, midpoints, bary, baryW, density = parser_viz(viz_file)
            select_paths(triangle_faces, triangles_weights, simple, midpoints, bary, baryW, density)
        except Exception as e:
            messagebox.showerror("Error", f"Oh no, something bad happend with the file, make sure you oppend correct one:\n{e}")

def handle_experiment(discretization_vars, algorithm_vars):
   
    selected_discretization_methods = [method for method, var in discretization_vars.items() if var.get()]
    selected_algorithms = [algo for algo, var in algorithm_vars.items() if var.get()]
  #beofre staritng the experiment, the user selects the discretization methods and the algorithms they want to test and comapre

    if not selected_discretization_methods or not selected_algorithms:
        messagebox.showwarning("Invalid Input", "Please, select at least one discretization method and at least one algorithm.")
        return

    random_points_type = ["random_simple", "random_skewed", "random_cluster", "random_boundary_points"]
    no_points_range = range(310, 600, 40)  
      # we define the range going from 4 to 1005, but the user can change the code.
    # I put this in order to generete the plots I will use in my paper, but for specific intervals it can be changed
    try:
        for point_type in random_points_type:
            for no_points in no_points_range:
                for discretization_method in selected_discretization_methods:
                    for shortest_path_algo in selected_algorithms:
                        outputName = point_type+"_"+discretization_method+"_"+shortest_path_algo+".csv"
                        terminal_comm = [the_computing_program, point_type, str(no_points), discretization_method, shortest_path_algo, outputName]
                        print("We are now running this command: " + ' '.join(terminal_comm))
                        subprocess.run(terminal_comm, check=True)

        messagebox.showinfo("Success", f"All experiments completed, results have been saved on your computer.")
    except subprocess.CalledProcessError as e:
        messagebox.showerror("Error", f"An error occurred while running the experiment:\n{e}")
    except Exception as e:
        messagebox.showerror("Error", f"An unexpected error occurred:\n{e}")

stage = tk.Tk()
stage.geometry("1200x600")
stage.title("CG Mark (short for benchmark)")

scene = tk.Frame(stage, padx=40, pady=40)
scene.pack(fill=tk.BOTH, expand=True)
get_input_button = tk.Button(scene, text="Input from File", command=get_file_for_viz)
get_input_button.grid(row=0, column=0, pady=5, sticky="ew")

run_modes = [("Random Simple Points:", "random_simple"), ("Random Skewed Points:", "random_skewed"), ("Random Cluster Points:", "random_cluster"), ("Random Boundary Points:", "random_boundary_points")]

arguments = {}
for i, (title, run_mode) in enumerate(run_modes, start=1): # for each mode we create a button for generate, a textfiled area to input the no of points to use for the triangualtion
    tk.Label(scene, text=title).grid(row=i, column=0, sticky="w")
    entry = tk.Entry(scene)
    entry.grid(row=i, column=1, sticky="ew")
    arguments[run_mode] = entry
    tk.Button(scene, text="Generate", command=lambda m=run_mode, e=entry: get_No_points(m, e)).grid(row=i, column=2, pady=5, sticky="ew")

direct_input_button = tk.Button(scene, text="Direct Input", command=direct_input)
direct_input_button.grid(row=5, column=0, pady=5, sticky="ew")
visualize_button = tk.Button(scene, text="Visualize Output", command=visualize_start)
visualize_button.grid(row=6, column=0, pady=5, sticky="ew")
tk.Label(scene, text="Discretization Options:").grid(row=7, column=0, sticky="w")
discretization_options = ["simple", "midpoints", "barycentric", "barycentricWeight", "densityWeight"]
disct_modes = {}
# Cwe create a checkbutton for each of the discretization methods and for each of the algos
for i, algo in enumerate(discretization_options):
    var = tk.BooleanVar(value=False)
    tk.Checkbutton(scene, text=algo, variable=var).grid(row=7, column=i+1, sticky="w")
    disct_modes[algo] = var  
tk.Label(scene, text="Pathfinding Algorithms:").grid(row=8, column=0, sticky="w")
shortest_path_algos = ["dijkstra", "astar"]
algorithms = {}
for i, algo in enumerate(shortest_path_algos):
    var = tk.BooleanVar(value=False)
    tk.Checkbutton(scene, text=algo, variable=var).grid(row=8, column=i+1, sticky="w")
    algorithms[algo] = var  

experiment_button = tk.Button(scene, text="Run Experiment", command=lambda: handle_experiment(disct_modes, algorithms))
experiment_button.grid(row=15, column=0, pady=7, sticky="ew")
scene.grid_columnconfigure(1, weight=1)
stage.mainloop()
