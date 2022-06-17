ES = list()
UniformeG = list()
estacionarios = list()
UniformeE = list()
memeticos1 = list()
memeticos2 = list()
memeticos3 = list()

TiemposES = list()
TUniformeG = list()
tiemposestacionarios = list()
TUniformeE = list()
tiemposmemeticos1 = list()
tiemposmemeticos2 = list()
tiemposmemeticos3 = list()

fichero = '/home/phuertas/UNIVERSIDAD/MH/PRACTICAS/P3/scripts/ILS.txt'

with open(fichero) as f:
    for linea in f:
        # Tu código aquí
        for i in linea.split():
            if i=="ILS":
                ES.append(linea.split())
            elif i=="TiempoILS":
                TiemposES.append(linea.split())


cadES = "".join( [str(_) for _ in ES] )
cadES = cadES.replace("[", "")
cadES = cadES.replace("]", "")
cadES = cadES.replace("'", "")
cadES = cadES.replace(",", "")
cadES = cadES.replace("ILS", "")
cadES = cadES.replace(" ", "\n")

print("ILS")
print(cadES)

print("\n")


cadTES = "".join( [str(_) for _ in TiemposES] )
cadTES = cadTES.replace("[", "")
cadTES = cadTES.replace("]", "")
cadTES = cadTES.replace("'", "")
cadTES = cadTES.replace(",", "")
cadTES = cadTES.replace("TiempoILS", "")
cadTES = cadTES.replace(" ", "\n")
print("Tiempos ILS")
print(cadTES)


