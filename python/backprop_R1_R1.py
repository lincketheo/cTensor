import matplotlib.pyplot as plt
import numpy as np
import random



def reject_outliers(data, m=2):
    return abs(data - np.mean(data)) < m * np.std(data)

def rand_btwn(lower, upper):
    return random.random() * (upper - lower) + lower


def linear_func(x, a_, b_):
    return a_ * x + b_
def linear_func_grad(x, a_, b_):
    return np.array([x, 1])

def polynomial(x, a_, b_, c_, d_, e_, f_):
    return a_ + b_ * x + c_ * x**2 + d_ * x**3 + e_ * x**4 + f_ * x**5
def polynomial_grad(x, a_, b_, c_, d_, e_, f_):
    return np.array([1, x, x**2, x**3, x**4, x**5])

def exp_func(x, a_, b_):
    return np.exp(a_ * x) + b_
def exp_func_grad(x, a_, b_):
    return np.array([x * np.exp(a_ * x), 1])

def oscil_func(x, a_, b_):
    return np.cos(a_/x) + b_
def oscil_func_grad(x, a_, b_):
    return np.array([(-1/x) * np.sin(a_ / x), 1])

def singularity(x, a_, b_):
    return a_/x + b_
def singularity_grad(x, a_, b_):
    return np.array([1/x, 1])


def linear_backprop(unknown_func, forward_func, forward_func_grad, num_unknown, num_forward):

    # Unkown Parameters
    unknown_args = [rand_btwn(-1, 1) for i in range(num_unknown)]
    print("Unknown: ", unknown_args)
    ########################

    # Propigation Parameters
    forward_args = [rand_btwn(-1, 1) for i in range(num_forward)]
    ########################
    

    n = 10000
    inputs = np.array([rand_btwn(-1, 1) for i in range(n)])
    outputs = np.array([unknown_func(i, *unknown_args) for i in inputs])

    ymax = max(outputs)
    ymin = min(outputs)

    # Meta data
    gamma = 0.1
    avg_err = 0
    err_prev = 0

    # Last 10 errors
    last_10 = np.array([])
    # Array of errors
    errs = np.array([])

    
    # For plotting data
    x = np.linspace(-10, 10, 1000)
    o1_0 = unknown_func(x, *unknown_args)
    o2_0 = forward_func(x, *forward_args)

    for i in range(n):
        out = forward_func(inputs[i], *forward_args)

        error = (out - outputs[i])**2
        avg_err = (i * avg_err + error) / (i + 1)
        errs = np.append(errs, error)

        last_10 = np.append(last_10, error)
        if(len(last_10) > 10):
            last_10 = np.delete(last_10, 0)

        err_prev = error

        
        # GRADIENT DESCENT
        grad = gamma * (out - outputs[i]) * forward_func_grad(inputs[i], *forward_args)
        # norm = np.sqrt(grad[0]**2 + grad[1]**2)

        for i in range(num_forward):
            forward_args[i] -= grad[i]

        plt.scatter(x, unknown_func(x, *unknown_args), color = "black", s = 5)
        plt.scatter(x, forward_func(x, *forward_args), color = "red", s = 5)
        plt.ylim(-10, 10)
        plt.xlim([-5, 5])
        plt.axvline(x=-1)
        plt.axvline(x=1)
        plt.pause(0.05)
        plt.clf()


    #  fig, (errors) = plt.subplots(1, 1)

    # Initial plot
    #  initial.scatter(x, o1_0, color = "black", s = 5)
    #  initial.scatter(x, o2_0, color = "red", s = 5)
    #  #  initial.set_ylim([min(0, b), max(np.exp(1) + b, np.exp(1))])
    #  initial.set_xlim([-1, 1])
    #
    #  # Final Plot
    #  o1 = unknown_func(x, a, b)
    #  o2 = forward_func(x, a0, b0)
    #  final.scatter(x, o1, color = "black", s = 5)
    #  final.scatter(x, o2, color = "red", s = 5)
    #  #  final.set_ylim([min(0, b), max(np.exp(1) + b, np.exp(1))])
    #  final.set_xlim([-1, 1])
    #
    # Err
    errors.scatter(np.linspace(0, n - 1, n), errs, color = "black", s = 5)
    errors.set_title(f"F_ext(x) = {a}x + {b} \n Starting F_f(x) = {a00}x + {b00} \n Ending F_f(x) = {a0}x + {b0}")
    errors.set_xlabel("Itteration")
    errors.set_ylabel("L2 Error of F_ext and F_f")

    plt.show()

linear_backprop(exp_func, polynomial, polynomial_grad, 2, 6)



