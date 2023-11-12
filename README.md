# LOOK A CAT
Aplicação 3D com animação a partir de comandos de telado, desenvolvida a partir do programa lookat, apresentado pelo professor Harlen Costa Batagelo, disponível no link https://hbatagelo.github.io/abcgapps/src/lookat.zip.

Alunos:

Bruno Bertolini Rabello     RA:11070715

Giovana Silva Reis          RA:11109015

**DESCRIÇÃO DO PROJETO**

- A aplicação consiste em um cenário 3D, composto por um Chão, um Gato e um observador.
- É possível interagir com a aplicação de duas maneiras:
  - Utilizando as setas do teclado, onde é possível rotacionar o Gato com os comandos LEFT e RIGHT, e movimentar o Gato juntamente com o Observador através dos comandos UP e DOWN
  - Acionando com o mouse os botões de incremento e decremento das componentes da escala RGB, que se encontram na janela disponível na lateral esquerda, para alterar a cor do Gato.

**Impelementação:**
*Ground*

- O objeto que cria o chão segue o mesmo disponibilizado na aplicação lookat.

*Cat*
A classe Cat, além dos métodos padrões (create, paint, updadte, destroy), também possui o método loadModelFromFile, onde o arquivo cat.obj é lido para criar a forma. Este método também foi retirado da aplicação lookat.
- update:
  - Incrementa as coordenadas x e z a partir do ângulo em que o objeto gato se encotra para fazer o objeto caminhar na tela
  - O valor speed é configurado no window.cpp onde o valor pode ser 1.0f ou -1.0f
  - As componentes da escala RGB são atualizadas com o valor configurado após acionamento dos botões de incremento ou decremento (também definidos no arquivo window.cpp)
  
      void Cat::update(float speed, float deltaTime, float red, float green, float blue){
        m_translation.x += sinf(glm::radians(m_rotation)) * speed * deltaTime;
        m_translation.z += cosf(glm::radians(m_rotation)) * speed * deltaTime;
        m_red = red;
        m_green = green;
        m_blue = blue;
      }

*Camera*
- Objeto Camera segue mesma implementação da aplicação lookat

*Window*
- onEvent:
  - Ao preccionar as setas UP ou DOWN
    - São atualizadas as variáveis m_catSpeed, utilizada posteriormente como parâmetro na chamada do método update() da classe Cat.
    - São atualizadas as variáveis m_dollySpeed e m_truckSpeed, utilizadas posteriormente como parâmetros dos métodos dolly() e truck() da classe Camera, respectivamente. A atualização desses parâmetros são feitas utilizando as funções seno e cosseno, a partir do angulo de rotação do objeto Cat, para que a Camera acompanhe o Gato.
  -Ao pressionar as setas LEFT ou RIGHT, a variável m_catRotation é configurada com valor 0.1f ou -0.1f, respectivamente. Este valor é utilizado como incremento da variável m_rotation da classe Cat, o que faz com que o Gato rotacione na tela.
  - Ao liberar a tecla pressionada, os valores configurados nas variáveis m_catSpeed, m_catRotation, m_dollySpeed e m_truckSpeed são configuradas com valor 0.

        void Window::onEvent(SDL_Event const &event) {
          if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w) {
              m_catSpeed = +1.0f;
              m_dollySpeed = -cosf(glm::radians(m_cat.m_rotation));
              m_truckSpeed = sinf(glm::radians(m_cat.m_rotation));
            }
            if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s) {
              m_catSpeed = -1.0f;
              m_dollySpeed = -cosf(glm::radians(m_cat.m_rotation+180));
              m_truckSpeed = sinf(glm::radians(m_cat.m_rotation+180));
            }
            if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a) {
              m_catRotation = 0.1f;
            }
            if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d) {
              m_catRotation = -0.1f;
            }
            // if (event.key.keysym.sym == SDLK_q)
            //   m_truckSpeed = -1.0f;
            // if (event.key.keysym.sym == SDLK_e)
            //   m_truckSpeed = 1.0f;
          }
        .
        .
        .
        }

- onPaintUi:
  - Definida a janela "Cores", que apresenta os botões de incremento e decremento das componentes da escala RGB. O delta aplicado é de 0.25f.
        void Window::onPaintUI() { 
          abcg::OpenGLWindow::onPaintUI();
        
          // Window begin
          ImGui::Begin("Cores");  
          if (ImGui::Button("+ Red", ImVec2(100, 50))) {
            m_red += 0.25f;
          }
          if (ImGui::Button("- Red", ImVec2(100, 50))) {
            m_red -= 0.25f;
          }
          if (ImGui::Button("+ Green", ImVec2(100, 50))) {
            m_green += 0.25f;
          }
          if (ImGui::Button("- Green", ImVec2(100, 50))) {
            m_green -= 0.25f;
          }
          if (ImGui::Button("+ Blue", ImVec2(100, 50))) {
            m_blue += 0.25f;
          }
          if (ImGui::Button("- Blue", ImVec2(100, 50))) {
            m_blue -= 0.25f;
          }
          ImGui::End();
      }

- onUpdate:
  - Chama os métodos dolly, truck e pan da classe Camera e o método update da classe Gato passando como parâmetros os valores configurados no método onEvent.
  - Incrementa a variável m_rotation da classe Cat de acordo com o valor configurado no método onEvent.

        void Window::onUpdate() {
          auto const deltaTime{gsl::narrow_cast<float>(getDeltaTime())};
        
          // Update LookAt camera
          m_camera.dolly(m_dollySpeed * deltaTime);
          m_camera.truck(m_truckSpeed * deltaTime);
          m_camera.pan(m_panSpeed * deltaTime);
          m_cat.m_rotation += m_catRotation;
          m_cat.update(m_catSpeed, deltaTime, m_red, m_green, m_blue);
        
        }
