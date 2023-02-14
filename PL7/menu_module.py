from  datetime import timedelta, datetime
import datetime
import requests


menu_options = {
    'current': 'get current forecast\n>>>>current %city%',
    'forecast': 'get forecast for several days\n>>>> forecast %city% %days%',
    'setunit': 'set uint\n>>>> setunit %unit%',
    'getunit': 'get uint\n>>>> getuint',
    'exit': 'exit',
}


def print_menu():
    for k, v in menu_options.items():
        print (k, '--', v)


def get_coord(city_name):
     params = {'q': city_name, 'format': 'geocodejson'}
     coord = requests.get('https://nominatim.openstreetmap.org/search?', params=params)

     if coord.status_code != 200:
          return None

     coord = coord.json()

     if len(coord['features']) == 0:
          print(f'There is no city with name {city_name}')
          coord = coord['features']
          return coord
     else:
          coord = coord['features'][0]['geometry']['coordinates']
          return coord


def current(city_name, unit):
    coord = get_coord(city_name)

    if coord == None:
        return None

    if len(coord) == 0:
        return None
    else:
        if unit == 'c':
            u_par = 'celsius'
        if unit == 'f':
            u_par = 'fahrenheit'
        params = {'latitude': coord[1], 
                  'longitude': coord[0], 
                  'temperature_unit': u_par, 
                  'current_weather': 'true'}

    forecast_data = requests.get('https://api.open-meteo.com/v1/forecast?', params=params)

    if forecast_data.status_code != 200:
        print('Connecting error')
        return None

    forecast_data = forecast_data.json()
    temprature = forecast_data['current_weather']['temperature']
    print(f'Current temp is {temprature}{unit.upper()}')


def forecast(city_name, fcst_days, unit):
    days = int(fcst_days)

    if days  < 1 or days > 16:
        print('Date interval is from 1 to 16 days')
        return None

    coord = get_coord(city_name)
    if coord == None:
        return None

    dateInterval = datetime.datetime.today()
    dateInterval = dateInterval.replace(minute=0, hour=0)

    if len(coord) == 0:
        return None
    else:
        if unit == 'c':
            u_par = 'celsius'
        if unit == 'f':
            u_par = 'fahrenheit'
        params = {'latitude': coord[1], 
                  'longitude': coord[0],
                  'hourly': 'temperature_2m', 
                  'temperature_unit': u_par,
                  'start_date': dateInterval.strftime('%Y-%m-%d'),
                  'end_date': (dateInterval + timedelta(days=days)).strftime('%Y-%m-%d')}

    forecast_data = requests.get('https://api.open-meteo.com/v1/forecast?', params=params)
    if forecast_data.status_code != 200:
        print('Connecting error')
        return None

    forecast_data = forecast_data.json()
    temprature = []
    cntr = 0

    for i in range(0, days*24):
        temprature.append(forecast_data['hourly']['temperature_2m'][i])

        if i%24 ==  5 or i%24 == 11 or i%24 == 17 or i%24 == 23:
            print(
                f"{dateInterval.strftime('%d/%m/%Y %H:%M')}"
                f"-{(dateInterval + timedelta(hours=5)).strftime('%H:%M')}"
                f"\tmin: {min(temprature)}{unit.upper()} "
                f"\tmax: {max(temprature)}{unit.upper()}")
            dateInterval = dateInterval + timedelta(hours=6)
            temprature.clear()


def setunit(unitArg, unit):
    parUnit = unitArg.lower()

    if parUnit == 'f' or parUnit == 'fahrenheit':
        return 'f'
    elif parUnit == 'c' or parUnit == 'celsius':
        return 'c'
    else:
        print(
            'There are only \'celsius\''
            '(\'c\') and \'fahrenheit\' (\'f\')')
        return unit


def getunit(unit):
     if unit == 'f':
        print('fahrenheit')
     if unit == 'c':
        print('celsius')