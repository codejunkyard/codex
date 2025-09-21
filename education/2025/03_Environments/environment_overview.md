# Development Environments for This Course

Our tooling for the entire course revolves around **Visual Studio Code (VS Code)**. Whether you are working entirely in the cloud or on your own hardware, we will rely on VS Code's consistent interface, extensions, and integrated terminal to keep every workflow familiar.

## Codespaces (Primary Starting Point)
- **What it is:** GitHub Codespaces provides a cloud-hosted development environment that launches directly from your repository.
- **Why we use it first:**
  - Instant provisioning with VS Code in the browser or the desktop application.
  - Identical configuration for every student, minimizing setup issues.
  - Built-in compute resources and preconfigured tooling tailored for this curriculum.
- **How it fits the course:** All initial exercises and examples assume you are working inside a Codespace so we can move quickly into the material without spending time on local setup.

## Windows 11 with VS Code Desktop
- **What it is:** Developing directly on a Windows 11 installation using the native VS Code application.
- **Considerations:**
  - Some command-line tools behave differently compared to Unix-like environments.
  - Requires you to install language runtimes and tooling manually.
  - Works well for graphical tools or Windows-specific workflows.
- **Course context:** While Windows 11 can host VS Code comfortably, we encourage pairing it with Windows Subsystem for Linux (WSL) to more closely mirror the Linux-based instructions used throughout the course.

## Windows Subsystem for Linux (WSL) on Windows 11
- **What it is:** A lightweight virtualized Linux environment running alongside Windows, accessible directly from VS Code.
- **Benefits:**
  - Provides a genuine Linux command-line experience without leaving Windows.
  - Integrates tightly with VS Code through the Remote Development extensions.
  - Supports the same tooling and scripts we use in Codespaces, making transitions seamless.
- **Course roadmap:** After you are comfortable in Codespaces, we will guide you through setting up WSL so you can reproduce the same workflows locally while leveraging Windows for everyday tasks.

## Native Linux Distribution
- **What it is:** Installing VS Code on a dedicated Linux distribution such as Ubuntu, Fedora, or Debian.
- **Strengths:**
  - Maximum control over the system environment with direct access to Linux tooling.
  - Often preferred for advanced users who want full customization and resource efficiency.
- **Course perspective:** This option mirrors the environments used in industry and in Codespaces. You are welcome to use a native Linux system if you already have one, but onboarding instructions will center on Codespaces and WSL.

## macOS with VS Code
- **What it is:** Running VS Code on macOS with the built-in Unix-like terminal and toolchain.
- **Highlights:**
  - Strong command-line support via zsh and Homebrew for package management.
  - Smooth performance on Apple Silicon and deep integration with macOS features.
- **Course perspective:** macOS can follow most Linux-oriented instructions with minor adjustments. You may use macOS if it is your primary machine, though the official walkthroughs will still focus on Codespaces and WSL to maintain parity across the cohort.

## Progression Summary
1. **Start in Codespaces** to ensure everyone has the same baseline environment and tooling inside VS Code.
2. **Transition to WSL on Windows 11** once you are ready to mirror the Linux-based workflow locally.
3. **Explore native Linux or macOS** setups if you need additional flexibility or already have experience managing those systems.

By standardizing on VS Code and clearly defining our target environments, we can spend more time mastering the course material and less time troubleshooting local configuration issues.
