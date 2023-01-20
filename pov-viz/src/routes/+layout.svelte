<script>
	import './styles.css';
</script>

<div class="app">

	<main>
		<slot />
	</main>

	<footer>

	</footer>
</div>

<style>
	.app {
		display: flex;
		flex-direction: column;
		min-height: 100vh;
	}

	main {
		width: 100%;
		height: 100vh;
	}
</style>
