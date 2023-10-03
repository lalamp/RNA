# Classe para representar os dados
class Lagarto:
    def __init__(self, massa, comprimento_passagem_ar, dimensao_pata_posterior, sexo):
        self.massa = massa
        self.comprimento_passagem_ar = comprimento_passagem_ar
        self.dimensao_pata_posterior = dimensao_pata_posterior
        self.sexo = sexo

    def __str__(self):
        return f"Massa: {self.massa:.6f}, Comprimento da Passagem de Ar: {self.comprimento_passagem_ar:.6f}, Dimensão da Pata Posterior: {self.dimensao_pata_posterior:.6f}, Sexo: {self.sexo}"

def main():
  try:
    p = float(input("Entre com o valor de p (0-1): "))
    if not 0 <= p <= 1:
      raise ValueError("O valor de p deve estar entre 0 e 1.")
  except ValueError as e:
    print(f"Erro: {e}")
    return

  data = get_data()
  train_data, test_data = get_train_test_data(data, p)

  train_data_norm, all_min, all_max = normalize_data(train_data)
  test_data_norm, _, _ = normalize_data(test_data)

  print_parameters(all_min, all_max)

  print_data("\nDados de treinamento normalizados", train_data_norm)
  print_data("\nDados de teste normalizados", test_data_norm)

  print("\nRegistrando um lagarto qualquer")
  lagarto = input_lagarto()

  if lagarto is not None:
    lagarto_norm = normalize_lagarto(lagarto, all_min, all_max)
    print("\nLagarto normalizado:", lagarto_norm)

# Função para obter dados de um arquivo
def get_data():
  data = []

  with open('', 'r') as file:
      lines = file.readlines()
      for line in lines:
          massa, comprimento_passagem_ar, dimensao_pata_posterior, sexo = line.strip().split(',')
          lagarto = Lagarto(float(massa), float(comprimento_passagem_ar), float(dimensao_pata_posterior), sexo.strip())
          data.append(lagarto)

  return data

# Função para dividir os dados em treinamento e teste
def get_train_test_data(data, p):
  masc = [lagarto for lagarto in data if lagarto.sexo == 'M']
  fem = [lagarto for lagarto in data if lagarto.sexo == 'F']

  split_index_masc = int(p * len(masc))
  split_index_fem = int(p * len(fem))

  train_data = masc[:split_index_masc] + fem[:split_index_fem]
  test_data = masc[split_index_masc:] + fem[split_index_fem:]

  return train_data, test_data

def get_min_max(attribute):
  return min(attribute), max(attribute)

# Função para normalizar os dados
def normalize_data(data):
  # Extrai atributos dos objetos lagartos
  massa = [lagarto.massa for lagarto in data]
  comprimento_passagem_ar = [lagarto.comprimento_passagem_ar for lagarto in data]
  dimensao_pata_posterior = [lagarto.dimensao_pata_posterior for lagarto in data]

  # Obtem os valores minimos e maximos para cada atributo
  min_massa, max_massa = get_min_max(massa)
  min_cpa, max_cpa = get_min_max(comprimento_passagem_ar)
  min_dpp, max_dpp = get_min_max(dimensao_pata_posterior)

  # Normaliza os valores de cada atributo
  massa_norm = [normalize_attribute(min_massa, max_massa, massa) for massa in massa]
  cpa_norm = [normalize_attribute(min_cpa, max_cpa, cpa) for cpa in comprimento_passagem_ar]
  dpp_norm = [normalize_attribute(min_dpp, max_dpp, dpp) for dpp in dimensao_pata_posterior]

  # Cria um novo array com os dados normalizados
  data_norm = [
    Lagarto(massa_norm[i], cpa_norm[i], dpp_norm[i], data[i].sexo)
    for i in range(len(data))
  ]

  # Array com os valores minimos e maximos de cada atributo
  all_min = [min_massa, min_cpa, min_dpp]
  all_max = [max_massa, max_cpa, max_dpp]

  return data_norm, all_min, all_max

# Função para normalizar um objeto Lagarto
def normalize_lagarto(lagarto, min_values, max_values):
    massa_norm = normalize_attribute(min_values[0], max_values[0], lagarto.massa)
    cpa_norm = normalize_attribute(min_values[1], max_values[1], lagarto.comprimento_passagem_ar)
    dpp_norm = normalize_attribute(min_values[2], max_values[2], lagarto.dimensao_pata_posterior)
    return Lagarto(massa_norm, cpa_norm, dpp_norm, lagarto.sexo)

def normalize_attribute(min_val, max_val, attribute):
  return 2 * ((attribute - min_val) / (max_val - min_val)) - 1

def print_parameters(min_values, max_values):
  print("\nParametros min e max do conjunto de treinamento")
  attributes = ["Massa", "Comprimento da Passagem de Ar", "Dimensão da Pata Posterior"]
  for attr, min_val, max_val in zip(attributes, min_values, max_values):
    print(f"{attr} - Min: {min_val:.6f}, Max: {max_val:.6f}")

def print_data(title, data):
  print(title)
  for lagarto in data:
    print(lagarto)

def input_lagarto():
  try:
    massa = float(input("Massa: "))
    comprimento_passagem_ar = float(input("Comprimento da Passagem de Ar: "))
    dimensao_pata_posterior = float(input("Dimensao da Pata Posterior: "))
    sexo = input("Sexo (M/F): ").upper()
    
    if sexo not in ("M", "F"):
      raise ValueError("Sexo deve ser 'M' ou 'F'.")

    return Lagarto(massa, comprimento_passagem_ar, dimensao_pata_posterior, sexo)
  except ValueError as e:
    print(f"Erro: {e}")
    return None

if __name__ == "__main__":
  main()