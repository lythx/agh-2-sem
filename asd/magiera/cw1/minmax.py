# Optymalna funkcja do wyszukania minimum i maksimum w tablicy
def minmax(t):
    n = len(t)
    max_val = t[-1]
    min_val = t[-1]
    # Skaczemy co 2 elementy dzięki czemu mamy tylko 3/2n porównań (robiąc "na pałe" jest 2n)
    # Ustawienie na początku t[-1] naprawia przypadek gdy n jest nieparzyste
    for i in range(0, n - 1, 2):
        if t[i] > t[i + 1]:
            mx = t[i]
            mn = t[i + 1]
        else:
            mx = t[i + 1]
            mn = t[i]
        max_val = max(max_val, mx)
        min_val = min(min_val, mn)
    return max_val, min_val
