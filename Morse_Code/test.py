import numpy as np

def main():
    # Input your transformation matrix
    rows = int(input("Enter the number of rows: "))
    cols = int(input("Enter the number of columns: "))

    matrix = np.zeros((rows, cols))

    print("Enter the transformation matrix elements row-wise:")
    for i in range(rows):
        for j in range(cols):
            matrix[i, j] = float(input(f"Element ({i + 1}, {j + 1}): "))

    # Perform Singular Value Decomposition (SVD)
    _, singular_values, _ = np.linalg.svd(matrix)

    # Calculate rank and nullity
    epsilon = np.finfo(float).eps
    rank = np.sum(singular_values > epsilon)
    nullity = cols - rank

    # Interpretation for a transformation matrix
    print(f"The transformation represented by the matrix:")
    print(f"  - Collapses to a subspace of dimension {nullity} (nullity)")
    print(f"  - Spans a subspace of dimension {rank} (rank)")

if __name__ == "__main__":
    main()
