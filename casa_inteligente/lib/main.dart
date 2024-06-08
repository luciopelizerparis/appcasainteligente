import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;

void main() {
  runApp(ControleCasa());
}

class ControleCasa extends StatelessWidget {
  final String serverAddress = "url_aws"; 
  final int serverPort = 3033;
  
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(
          title: Text('App Casa Inteligente'),
        ),
        body: Center(
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            children: <Widget>[
              ElevatedButton(
                onPressed: () => sendCommand('/acender'),
                child: Text('Acender LED'),
              ),
              ElevatedButton(
                onPressed: () => sendCommand('/apagar'),
                child: Text('Apagar LED'),
              ),
            ],
          ),
        ),
      ),
    );
  }

  void sendCommand(String command) async {
    final url = Uri.http(serverAddress, '$command');
    try {
      final response = await http.get(url);
      if (response.statusCode == 200) {
        print('Comando enviado com sucesso');
      } else {
        print('Erro ao enviar comando');
      }
    } catch (e) {
      print('Erro: $e');
    }
  }
}
