
# O alvo padrão (que roda só de digitar 'make')
all:
	@mkdir -p bin
	@cd bin && cmake .. && cmake --build .

# Alvo para compilar e já rodar o programa direto: 'make run'
run: all
	@./bin/Agenda_Mais

# Alvo para limpar tudo se der algum problema: 'make clean'
clean:
	@rm -rf bin
	@echo "Pasta bin removida com sucesso!"