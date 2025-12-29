import numpy as np
import matplotlib.pyplot as plt


plt.rcParams['font.sans-serif'] = ['DejaVu Sans']
plt.rcParams['axes.unicode_minus'] = False



def linear_fitting(filename):
    """
    Linear data fitting function using least squares method
    
    Input: filename - data file name (fitdata1.dat, fitdata2.dat, fitdata3.dat)
    
    Model:
        x' = a1*x + a2*y + a3
        y' = a4*x + a5*y + a6
    """
    
    print(f"\n{'='*60}")
    print(f"Processing file: {filename}")
    print('='*60)
    
    try:
        data = np.loadtxt(filename)
    except FileNotFoundError:
        print(f"Error: {filename} not found.")
        return None
    
    x = data[:, 0]
    y = data[:, 1]
    x_prime = data[:, 2]
    y_prime = data[:, 3]
    
    N = len(x)
    print(f"Number of data points (N): {N}")
    
    A = np.zeros((2*N, 6))
    b = np.zeros(2*N)
    
    A[0::2, 0] = x       # a1 coefficient
    A[0::2, 1] = y       # a2 coefficient
    A[0::2, 2] = 1       # a3 coefficient
    
    A[1::2, 3] = x       # a4 coefficient
    A[1::2, 4] = y       # a5 coefficient
    A[1::2, 5] = 1       # a6 coefficient
    
    b[0::2] = x_prime    # x' values
    b[1::2] = y_prime    # y' values
    
    a, residuals, rank, s = np.linalg.lstsq(A, b, rcond=None)
    
    print("\n=== Estimated Parameters ===")
    print(f"a1 = {a[0]:.8f}")
    print(f"a2 = {a[1]:.8f}")
    print(f"a3 = {a[2]:.8f}")
    print(f"a4 = {a[3]:.8f}")
    print(f"a5 = {a[4]:.8f}")
    print(f"a6 = {a[5]:.8f}")
    
    x_pred = a[0]*x + a[1]*y + a[2]
    y_pred = a[3]*x + a[4]*y + a[5]
    
    error_x = np.sum((x_pred - x_prime)**2)
    error_y = np.sum((y_pred - y_prime)**2)
    total_error = error_x + error_y
    
    print("\n=== Error Analysis ===")
    print(f"Squared error for x' equation: {error_x:.8f}")
    print(f"Squared error for y' equation: {error_y:.8f}")
    print(f"Total squared error: {total_error:.8f}")
    
    print("\n=== Data Comparison (First 5 samples) ===")
    print(f"{'i':<4} {'x':<12} {'y':<12} {'x_pred':<12} {'x_actual':<12} {'error':<12}")
    print("-" * 64)
    for i in range(min(5, N)):
        err = abs(x_pred[i] - x_prime[i])
        print(f"{i:<4} {x[i]:<12.4f} {y[i]:<12.4f} {x_pred[i]:<12.4f} {x_prime[i]:<12.4f} {err:<12.6f}")
    
    return {
        'parameters': a,
        'x_pred': x_pred,
        'y_pred': y_pred,
        'total_error': total_error,
        'x_original': x,
        'y_original': y,
        'x_prime': x_prime,
        'y_prime': y_prime
    }



def plot_results(results, filename):
    """
    Visualize results as plots
    """
    if results is None:
        return
    
    a = results['parameters']
    x = results['x_original']
    y = results['y_original']
    x_prime = results['x_prime']
    y_prime = results['y_prime']
    x_pred = results['x_pred']
    y_pred = results['y_pred']
    
    fig, axes = plt.subplots(2, 2, figsize=(12, 10))
    fig.suptitle(f"Linear Fitting Results: {filename}", fontsize=14, fontweight='bold')
    
    ax = axes[0, 0]
    ax.scatter(range(len(x_prime)), x_prime, label='Actual x_prime', alpha=0.6, s=30)
    ax.scatter(range(len(x_pred)), x_pred, label='Predicted x_prime', alpha=0.6, s=30)
    ax.set_xlabel('Data Index')
    ax.set_ylabel('x_prime Value')
    ax.set_title('x_prime Transformation (Actual vs Predicted)')
    ax.legend()
    ax.grid(True, alpha=0.3)
    
    ax = axes[0, 1]
    ax.scatter(range(len(y_prime)), y_prime, label='Actual y_prime', alpha=0.6, s=30)
    ax.scatter(range(len(y_pred)), y_pred, label='Predicted y_prime', alpha=0.6, s=30)
    ax.set_xlabel('Data Index')
    ax.set_ylabel('y_prime Value')
    ax.set_title('y_prime Transformation (Actual vs Predicted)')
    ax.legend()
    ax.grid(True, alpha=0.3)
    
    ax = axes[1, 0]
    error_x = x_pred - x_prime
    ax.scatter(range(len(error_x)), error_x, alpha=0.6, s=30, color='red')
    ax.axhline(y=0, color='k', linestyle='--', linewidth=0.8)
    ax.set_xlabel('Data Index')
    ax.set_ylabel('Error (Predicted - Actual)')
    ax.set_title('x_prime Error Distribution')
    ax.grid(True, alpha=0.3)
    
    ax = axes[1, 1]
    error_y = y_pred - y_prime
    ax.scatter(range(len(error_y)), error_y, alpha=0.6, s=30, color='red')
    ax.axhline(y=0, color='k', linestyle='--', linewidth=0.8)
    ax.set_xlabel('Data Index')
    ax.set_ylabel('Error (Predicted - Actual)')
    ax.set_title('y_prime Error Distribution')
    ax.grid(True, alpha=0.3)
    
    plt.tight_layout()
    
    output_filename = filename.replace('.dat', '_result.png')
    plt.savefig(output_filename, dpi=150, bbox_inches='tight')
    print(f"\nPlot saved: {output_filename}")
    plt.show()



def main():
    """
    Main function: process all data files
    """
    print("\n" + "="*60)
    print("Linear Data Fitting (Least Squares Method)")
    print("="*60)
    
    filenames = ['fitdata1.dat', 'fitdata2.dat', 'fitdata3.dat']
    
    all_results = {}
    
    for filename in filenames:
        results = linear_fitting(filename)
        if results is not None:
            all_results[filename] = results
            plot_results(results, filename)
    
    print("\n" + "="*60)
    print("Final Summary")
    print("="*60)
    
    for filename, results in all_results.items():
        a = results['parameters']
        print(f"\n{filename}:")
        print(f"  a1={a[0]:.6f}, a2={a[1]:.6f}, a3={a[2]:.6f}")
        print(f"  a4={a[3]:.6f}, a5={a[4]:.6f}, a6={a[5]:.6f}")
        print(f"  Total squared error: {results['total_error']:.6f}")



if __name__ == "__main__":
    main()
