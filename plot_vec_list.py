import matplotlib.pyplot as plt

def plot_access_times(acc_size, vec_arr, pa_vec_arr, list_arr, pa_list_arr):
    """Plt access times of vector & list"""

    plt.plot(acc_size, vec_arr, 'g--', label='vector')
    #plt.plot(acc_size, pa_vec_arr, 'b--', label='pa_vector')#Appears too close to vector
    plt.plot(acc_size, list_arr, 'r--', label='list')
    plt.plot(acc_size, pa_list_arr, 'y--', label='pa_list')

    plt.legend()

    plt.xlabel('Number of Elements accessed')
    plt.ylabel('Time in seconds')

    plt.show()

def read_access_times(fname)    :
    """Read the access times of vector & list;
    Return respective times as lists"""

    with open(fname) as f:
        array = []
        for line in f: # read rest of lines
            array.append([int(x) for x in line.split()])

    sizes   = [10, 50, 100, 500, 1000, 5000, 10000, 50000, 100000]
    vec     = [6.102e-06, 3.926e-06, 5.442e-06, 4.6759e-05, 0.000159818, 0.00281888, 0.0191507, 0.287412, 1.23868]
    pa_vec  = [5.37e-07, 1.623e-06, 3.691e-06, 4.1935e-05, 0.000141731, 0.00255352, 0.010369, 0.288493, 1.44419]
    lst     = [1.222e-06, 3.435e-06, 7.301e-06, 0.000115439, 0.000458982, 0.0415953, 0.195073, 11.5066, 66.8715]
    pa_lst  = [4.64e-07, 5.914e-06, 9.269e-06, 0.000114494, 0.000430064, 0.0495458, 0.198141,10.5939, 65.1523]

    return (sizes, vec, pa_vec, lst, pa_lst)

def plot_vec_list():
    """Plot access times"""

    times   = read_access_times("")
    plot_access_times(times[0], times[1], times[2], times[3], times[4])


if __name__ == "__main__":
    plot_vec_list()
