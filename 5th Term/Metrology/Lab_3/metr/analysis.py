import numpy as np
import matplotlib.pyplot as plt
import scipy as sp


def retrieve_data(filenames:list) -> dict:
    raw_datas = {}
    for i in filenames:
        try:
            temp_data=[]
            with open(f"./Measurements/{i}", "r") as File:
                # raw_datas.append(list(map(float, File.readlines().replace(",", "."))))
                for line in File.readlines():
                    temp_data.append(float(line.strip().replace("\n", "").split(",")[1]))
            raw_datas[i[:-4]] = temp_data
            # print(temp_data)
            # exit(0)
        except FileNotFoundError as e:
            print(f"Error:{e}")
    return raw_datas
# raw_data = np.random.normal(5, .01, 100)
# raw_data.sort()

def print_all_data(raw_datas:dict) -> None:
    for i in raw_datas:

        raw_data = raw_datas[i]
        print(i)
        # print(raw_data)

        stats = {}
        stats["Размер выборки"] = len(raw_data)
        stats["Минимальное значение"] = min(raw_data)
        stats["Максимальное значение"] = max(raw_data)
        stats["Среднекватратичное значение"] = np.std(raw_data)
        stats["Среднееарифметическое"] = sum(raw_data)/len(raw_data)
        stats["Медианное значение"] = np.median(raw_data)
        stats["Среднеквадратическое значение среднего арифметического"] = stats["Среднекватратичное значение"] / len(raw_data)**.5
        stats["Выборочная дисперсия"] = np.var(raw_data)
        stats["Коэффициент асимметрии"] = sp.stats.skew(raw_data)
        stats["Коэффициент эксцесса"] = sp.stats.kurtosis(raw_data)

        # for j in stats.keys():
        #     print(f"{j}: {stats[j]}")

        
        # x_theor = np.linspace(stats["Минимальное значение"]*.99, stats["Максимальное значение"]*1.01, 100)
        # y_theor = sp.stats.norm.pdf(x_theor, np.mean(raw_data), stats["Среднекватратичное значение"])
        # plt.plot(x_theor, y_theor, color="red", alpha=.6)

        fig, ax = plt.subplots(1)
        ax.hist(raw_data, bins=13, alpha=.6, color="blue", edgecolor="black")
        ax.axvline(x=stats["Медианное значение"], color="red", alpha=.7)
        ax.set_title(i[:-4], size=20)
        ax.grid(alpha=.3)
        fig.set_size_inches(12, 8)
        fig.savefig(f"./Measurements/{i}.png", dpi=300, bbox_inches="tight")   
        

if __name__ == "__main__":
    filenames = ["DC_voltage_measure.csv", "R1_resistance_measure.csv", "R2_resistance_measure.csv", "Gained_DC_voltage_measure.csv"]
    print_all_data(retrieve_data(filenames))


    