import requests
import openai

def leer_datos_thingspeak(read_api_key, channel_id, openai_api_key):
    URL = f'https://api.thingspeak.com/channels/{channel_id}/feeds.json?api_key={read_api_key}&results=2'

    try:
        response = requests.get(URL)
        response.raise_for_status()
        feeds = response.json()['feeds']
        for feed in feeds:
            temperatura = feed['field1']
            presion = feed['field2']
            print(f"Temperatura: {temperatura} °C, Presión: {presion} hPa")

            # Generar comando basado en los datos
            comando = generar_comando_openai(temperatura, presion, openai_api_key)
            print(comando)

    except requests.exceptions.HTTPError as err:
        print(f"Error en la solicitud HTTP: {err}")
    except Exception as e:
        print(f"Error: {e}")

def calcular_parametros_actuadores(temperatura, presion):
    temperatura = float(temperatura)

    # Establecer rangos y valores base
    temp_min = 20.0  # Temperatura mínima para operación
    temp_max = 35.0  # Temperatura máxima esperada
    duracion_base = 30  # Duración base en segundos
    frecuencia_base = 60  # Frecuencia base en minutos

    # Calcular el factor de aumento basado en la temperatura
    if temperatura < temp_min:
        accion = "apagar"
        duracion_segundos = 0
        frecuencia_minutos = 0
    else:
        accion = "encender"
        factor = (temperatura - temp_min) / (temp_max - temp_min)
        duracion_segundos = int(duracion_base + factor * (60 - duracion_base))  # hasta 60 segundos
        frecuencia_minutos = int(frecuencia_base - factor * (30 - frecuencia_base))  # hasta 30 minutos

    return accion, duracion_segundos, frecuencia_minutos



def generar_comando_openai(temperatura, presion, api_key):
    openai.api_key = api_key

    accion, duracion_segundos, frecuencia_minutos = calcular_parametros_actuadores(temperatura, presion)

    prompt = f"""
Based on the following conditions:
- Current Temperature: {temperatura} °C
- Current Pressure: {presion} hPa

Generate a command for controlling a water pump in a hydroponic system. The command should be in the format:
"[encender/apagar] motobomba por [duracion en segundos] cada [n] minutos"

Where "encender" or "apagar" is determined by the temperature and pressure conditions, "duracion en segundos" is the duration for which the pump should be active, and "[n] minutos" is the frequency of the pump operation.
"""

    response = openai.Completion.create(
      engine="davinci",
      prompt=prompt,
      max_tokens=100
    )

    comando = response.choices[0].text.strip()
    comando_formateado = f"{accion} motobomba por {duracion_segundos} segundos cada {frecuencia_minutos} minutos"

    return comando_formateado



leer_datos_thingspeak(read_api_key, channel_id, openai_api_key)

