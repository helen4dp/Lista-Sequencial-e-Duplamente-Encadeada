from pathlib import Path
arquivo_resultados = Path("resultados_testes_sequencial.csv")

print("Arquivo encontrado?", arquivo_resultados.exists())

import pandas as pd

df = pd.read_csv("resultados_testes_sequencial.csv")

import matplotlib.pyplot as plt

#determinando tamanho
plt.figure(figsize=(15, 8))

#linhas
plt.plot(df["n"], df["ins_inicio"], marker="o", label="Inserção no início")
plt.plot(df["n"], df["acesso_ind"], marker="o", label="Acesso por índice")
plt.plot(df["n"], df["rem_inicio"], marker="o", label="Remoção no início")
plt.plot(df["n"], df["rem_meio"], marker="o", label="Remoção no meio")
plt.plot(df["n"], df["percurso"], marker="o", label="Percurso")

#configuraçoes do gráfico
plt.xticks(df["n"])
plt.xlabel("Tamanho do vetor (n)")
plt.ylabel("Tempo médio (em nanossegundos)")

plt.xscale("log")
plt.yscale("log")

plt.title("Tempo de execução — 5 operações da Lista Sequencial")
plt.legend()
plt.grid()

plt.show()

