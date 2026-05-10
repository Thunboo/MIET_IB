#!/usr/bin/python3

def vector_from_degrees(degrees, length):
    """
    Создает вектор по степеням многочлена
    Например, degrees = [0, 3, 5] соответствует 1 + x^3 + x^5
    Индекс 0 соответствует x^0
    """
    vector = [0] * length

    for degree in degrees:
        vector[degree] = 1

    return vector


def xor_vectors(a, b):
    """
    Сложение двух векторов по модулю 2
    """
    if len(a) != len(b):
        raise ValueError("Длины векторов должны совпадать")

    return [x ^ y for x, y in zip(a, b)]


def polynomial_from_vector(vector, name):
    """
    Формирует строку многочлена по вектору битов
    """
    terms = []

    for degree, bit in enumerate(vector):
        if bit == 0:
            continue

        if degree == 0:
            terms.append("1")
        elif degree == 1:
            terms.append("x")
        else:
            terms.append(f"x^{degree}")

    if not terms:
        return f"{name}(x) = 0"

    return f"{name}(x) = " + " + ".join(terms)

def print_markdown_table_1_2(I1, Y1, Z1, Y2, I2):
    """
    Выводит Таблицу 1.2 в Markdown-формате
    """
    print("=" * 72)
    print("Таблица 1.2 – Работа системы скремблер – дескремблер")
    print("=" * 72)
    print("|  № | I1 | Y1 | Z1/Z2 | Y2 | I2 |")
    print("|----|----|----|-------|----|----|")

    for k in range(len(I1)):
        print(f"| {k:2} | {I1[k]:2} | {Y1[k]:2} | {Z1[k]:^5} | {Y2[k]:2} | {I2[k]:2} |")


def visualize(labels, arrays):
    """Визуализирует сигналы"""
    print()
    print("=" * 72)
    print("Визуализация сигналов")
    print("=" * 72)
    print()

    for label, arr in zip(labels, arrays):
        wave = "".join("▒" if bit else "_" for bit in arr)
        print(f"{label:<15} {wave}")

    print()
    print("Такт:           " + "".join(str(i % 10) for i in range(len(arrays[0]))))


def lfsr(init_state, steps, taps=(3, 5, 7, 12)):
    """
    Генератор ПСП
    """
    state = init_state[:]
    output = []

    for _ in range(steps):
        out = 0

        for tap in taps:
            out ^= state[tap - 1]

        output.append(out)

        # Сдвиг вправо: новый бит записывается в R1
        state = [out] + state[:-1]

    return output


# -----------------
# Исходные данные |
# -----------------

# Y1(x)=x^34+x^33+x^32+x^31+x^29+x^28+x^27+x^26+x^25+
#       x^21+x^19+x^16+x^15+x^14+x^13+x^11+x^9+x^7+x^6+x^5+x^3+1
Y1_DEGREES = [0, 3, 5, 6, 7, 9, 11, 13, 14, 15, 16, 19, 21, 25, 26, 27, 28, 29, 31, 32, 33, 34]

# I1(x)=1+x+x^2+x^3+x^4+x^5+x^6+x^7+x^8+x^9+x^10+x^11+
#       x^12+x^18+x^20+x^22+x^25+x^26+x^29
I1_DEGREES = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 18, 20, 22, 25, 26, 29]

N = max(max(Y1_DEGREES), max(I1_DEGREES)) + 1


# --------------------------------------
# Расчет системы скремблер-дескремблер |
# --------------------------------------

I1 = vector_from_degrees(I1_DEGREES, N)
Y1 = vector_from_degrees(Y1_DEGREES, N)

# Скремблирование
Z1 = xor_vectors(I1, Y1)

# Канал без ошибок
Z2 = Z1[:]

# Генератор ПСП на приемнике работает синхронно
Y2 = Y1[:]

# Дескремблирование
I2 = xor_vectors(Z2, Y2)


# ----------
# Проверка |
# ----------

if I2 != I1:
    mismatches = [i for i in range(N) if I1[i] != I2[i]]
    raise RuntimeError(f"Ошибка: I2 не совпадает с I1 на тактах {mismatches}")

print("✅ Проверка успешна: Выходной информативный сигнал\nполностью совпадает с входным.")


# -------------------
# Вывод многочленов |
# -------------------

print()
print(polynomial_from_vector(I1, "I1"))
print(polynomial_from_vector(Y1, "Y1"))
print(polynomial_from_vector(Z1, "Z1"))
print(polynomial_from_vector(Z2, "Z2"))
print(polynomial_from_vector(Y2, "Y2"))
print(polynomial_from_vector(I2, "I2"))


# ----------------
# Вывод векторов |
# ----------------

print()
print("Векторные представления:")
print(f"I1    = {''.join(map(str, I1))}")
print(f"Y1    = {''.join(map(str, Y1))}")
print(f"Z1/Z2 = {''.join(map(str, Z1))}")
print(f"Y2    = {''.join(map(str, Y2))}")
print(f"I2    = {''.join(map(str, I2))}")


# -------------
# Таблица 1.2 |
# -------------

print_markdown_table_1_2(I1, Y1, Z1, Y2, I2)

# --------------
# Визуализация |
# --------------

labels = ["I1 (вход)", "Y1 (ПСП)", "Z1 (линия)", "I2 (выход)"]
arrays = [I1, Y1, Z1, I2]

visualize(labels, arrays)
