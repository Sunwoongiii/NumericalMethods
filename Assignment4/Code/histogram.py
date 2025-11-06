import numpy as np
import matplotlib.pyplot as plt
from pathlib import Path

def load_samples(filename):
    try:
        samples = np.loadtxt(filename)
        return samples
    except FileNotFoundError:
        print(f"Error: File {filename} not found")
        return None

def plot_histogram(ax, samples, bins, title, color, expected_range=None):
    if samples is None or len(samples) == 0:
        return
    mean = np.mean(samples)
    std = np.std(samples, ddof=1)
    counts, bin_edges, patches = ax.hist(samples, bins=bins, density=True, 
                                         alpha=0.7, color=color, edgecolor='black', linewidth=0.5)
    ax.axvline(mean, color='red', linestyle='--', linewidth=2, label=f'Mean: {mean:.4f}')
    ax.set_title(f'{title}\nN = {len(samples)}', fontsize=12, fontweight='bold')
    ax.set_xlabel('Value', fontsize=10)
    ax.set_ylabel('Density', fontsize=10)
    ax.legend(loc='upper right', fontsize=8)
    ax.grid(True, alpha=0.3)
    stats_text = f'Mean: {mean:.4f}\nStd: {std:.4f}'
    ax.text(0.02, 0.98, stats_text, transform=ax.transAxes, 
            fontsize=9, verticalalignment='top',
            bbox=dict(boxstyle='round', facecolor='wheat', alpha=0.5))

def create_uniform_histograms(sample_sizes, a=-3, b=4, bins=100):
    fig, axes = plt.subplots(2, 2, figsize=(14, 10))
    fig.suptitle(f'Uniform Distribution Histograms [a={a}, b={b}]', 
                 fontsize=16, fontweight='bold')
    axes = axes.flatten()
    for i, n in enumerate(sample_sizes):
        filename = f'uniform_{n}.txt'
        samples = load_samples(filename)
        if samples is not None:
            plot_histogram(axes[i], samples, bins, 'Uniform Distribution', 'skyblue', (a, b))
    plt.tight_layout()
    plt.savefig('uniform_histograms.png', dpi=300, bbox_inches='tight')
    print("Saved: uniform_histograms.png")
    plt.show()

def create_gaussian_histograms(sample_sizes, m=0.5, s=1.5, bins=100):
    fig, axes = plt.subplots(2, 2, figsize=(14, 10))
    fig.suptitle(f'Gaussian Distribution Histograms [mean={m}, std={s}]', 
                 fontsize=16, fontweight='bold')
    axes = axes.flatten()
    for i, n in enumerate(sample_sizes):
        filename = f'gaussian_{n}.txt'
        samples = load_samples(filename)
        if samples is not None:
            plot_histogram(axes[i], samples, bins, 'Gaussian Distribution', 'lightcoral')
            x = np.linspace(samples.min(), samples.max(), 1000)
            theoretical = (1 / (s * np.sqrt(2 * np.pi))) * np.exp(-0.5 * ((x - m) / s) ** 2)
            axes[i].plot(x, theoretical, 'b-', linewidth=2, label=f'Theoretical N({m},{s}²)')
            axes[i].legend(loc='upper right', fontsize=8)
    plt.tight_layout()
    plt.savefig('gaussian_histograms.png', dpi=300, bbox_inches='tight')
    print("Saved: gaussian_histograms.png")
    plt.show()

def create_comparison_plot(sample_sizes):
    fig = plt.figure(figsize=(16, 10))
    for i, n in enumerate(sample_sizes):
        ax1 = plt.subplot(2, 4, i+1)
        filename = f'uniform_{n}.txt'
        samples = load_samples(filename)
        if samples is not None:
            ax1.hist(samples, bins=100, density=True, alpha=0.7, 
                     color='skyblue', edgecolor='black', linewidth=0.5)
            ax1.set_title(f'Uniform (N={n})', fontsize=10, fontweight='bold')
            ax1.set_xlabel('Value', fontsize=8)
            ax1.set_ylabel('Density', fontsize=8)
            ax1.grid(True, alpha=0.3)
            ax1.axhline(1/7, color='red', linestyle='--', linewidth=2, label='Theoretical')
            ax1.legend(fontsize=7)
        ax2 = plt.subplot(2, 4, i+5)
        filename = f'gaussian_{n}.txt'
        samples = load_samples(filename)
        if samples is not None:
            ax2.hist(samples, bins=100, density=True, alpha=0.7, 
                     color='lightcoral', edgecolor='black', linewidth=0.5)
            ax2.set_title(f'Gaussian (N={n})', fontsize=10, fontweight='bold')
            ax2.set_xlabel('Value', fontsize=8)
            ax2.set_ylabel('Density', fontsize=8)
            ax2.grid(True, alpha=0.3)
            x = np.linspace(samples.min(), samples.max(), 1000)
            theoretical = (1 / (1.5 * np.sqrt(2 * np.pi))) * np.exp(-0.5 * ((x - 0.5) / 1.5) ** 2)
            ax2.plot(x, theoretical, 'b-', linewidth=2, label='Theoretical')
            ax2.legend(fontsize=7)
    plt.suptitle('Convergence of Histograms with Sample Size', 
                 fontsize=16, fontweight='bold')
    plt.tight_layout()
    plt.savefig('comparison_histograms.png', dpi=300, bbox_inches='tight')
    print("Saved: comparison_histograms.png")
    plt.show()

def print_statistics(sample_sizes):
    print("\n" + "="*80)
    print("STATISTICS SUMMARY")
    print("="*80)
    print("\n[UNIFORM DISTRIBUTION: a=-3, b=4]")
    print(f"{'N':<10} {'Mean':<12} {'Std Dev':<12} {'Theoretical Mean':<20} {'Theoretical Std':<20}")
    print("-"*80)
    for n in sample_sizes:
        filename = f'uniform_{n}.txt'
        samples = load_samples(filename)
        if samples is not None:
            mean = np.mean(samples)
            std = np.std(samples, ddof=1)
            theo_mean = 0.5
            theo_std = np.sqrt((4-(-3))**2 / 12)
            print(f"{n:<10} {mean:<12.4f} {std:<12.4f} {theo_mean:<20.4f} {theo_std:<20.4f}")
    print("\n[GAUSSIAN DISTRIBUTION: mean=0.5, std=1.5]")
    print(f"{'N':<10} {'Mean':<12} {'Std Dev':<12} {'Theoretical Mean':<20} {'Theoretical Std':<20}")
    print("-"*80)
    for n in sample_sizes:
        filename = f'gaussian_{n}.txt'
        samples = load_samples(filename)
        if samples is not None:
            mean = np.mean(samples)
            std = np.std(samples, ddof=1)
            theo_mean = 0.5
            theo_std = 1.5
            print(f"{n:<10} {mean:<12.4f} {std:<12.4f} {theo_mean:<20.4f} {theo_std:<20.4f}")
    print("\n" + "="*80)

def main():
    print("="*80)
    print("Random Number Generation - Histogram Visualization")
    print("="*80)
    sample_sizes = [100, 1000, 10000, 100000]
    print("\nCreating uniform distribution histograms...")
    create_uniform_histograms(sample_sizes)
    print("\nCreating Gaussian distribution histograms...")
    create_gaussian_histograms(sample_sizes)
    print("\nCreating comparison plot...")
    create_comparison_plot(sample_sizes)
    print_statistics(sample_sizes)
    print("\n" + "="*80)
    print("DISCUSSION: Shape of Histograms vs. Number of Samples")
    print("="*80)
    print("""
As the number of samples increases:

1. UNIFORM DISTRIBUTION:
   - N=100: Histogram shows high variability with irregular bins
   - N=1000: Shape becomes more rectangular but still noisy
   - N=10000: Clearly approaching uniform flat distribution
   - N=100000: Very smooth, almost perfectly flat rectangular shape
   
2. GAUSSIAN DISTRIBUTION:
   - N=100: Shows rough bell shape but with significant noise
   - N=1000: Bell shape is clearer with some irregularities
   - N=10000: Smooth bell curve closely matching theoretical curve
   - N=100000: Almost perfectly matches the theoretical Gaussian curve
   
3. LAW OF LARGE NUMBERS:
   - Sample mean converges to theoretical mean
   - Sample variance converges to theoretical variance
   - Histogram shape converges to theoretical probability density
   
4. CONVERGENCE RATE:
   - Standard error decreases as 1/sqrt(N)
   - For accurate distribution shape, N >= 10000 is recommended
   - For smooth density estimation, N >= 100000 is ideal
""")
    print("="*80)
    print("All histograms generated successfully!")
    print("="*80)

if __name__ == "__main__":
    main()
